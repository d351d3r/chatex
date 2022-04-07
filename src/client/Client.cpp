#include "headers/Client.hpp"
#include "headers/talk_helper.hpp"

#include <boost/thread.hpp>
#include <chrono>
#include <thread>
#include <iostream>

namespace client {

    namespace {
        using namespace boost::asio;
        const std::string kEndOfFile = "read: End of file";
        const int kPingSleepMS = 2'000;
    } // namespace

    Client::Client() : talker_() {}

    void Client::Run(bool is_response_print) try {
        talker_.is_response_print_ = is_response_print;
        if (!talker_.IsConnected()) {
            std::cout << "Connect to server before you do requests" << std::endl;
            return;
        }
        boost::thread ping_thread([&]() { RunPing(); });
        while (true) {
            talker_.TryDoRequest();
            if (!talker_.IsConnected()) {
                ping_thread.join();
                std::cout << "Connection stopped." << std::endl;
                return;
            }
            talker_.TryRead();
            if (!talker_.IsConnected()) {
                ping_thread.join();
                std::cout << "Connection stopped." << std::endl;
                return;
            }
        }
    } catch (...) {
        std::cout << "Connection dropped. Last request hadn't sent." << std::endl;
    }

    void Client::RunPing() try {
        if (!talker_.IsConnected()) {
            return;
        }
        while (true) {
            if (!talker_.IsConnected()) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(kPingSleepMS));
            if (!talker_.IsLogedIn()) {
                continue;
            }
            talker_.DoPing();
            if (!talker_.IsConnected()) {
                return;
            }
            talker_.TryRead();
        }
    } catch (...) {}

    void Client::Talker::DoPing() {
        if (!connected_) {
            return;
        }
        mutex_.lock();
        ++id_transaction_;
        mutex_.unlock();

        auto request = talk_helper::MakePingRequest("ping", id_transaction_,
                                                    session_uuid_);
        if (request.message) {
            DoWrite(*request.message);
        }
    }

    bool Client::Talker::IsLogedIn() const {
        return session_uuid_.has_value();
    }

    void Client::Talker::Disconnect() {
        connected_ = false;
        login_ = std::nullopt;
        possible_login_ = std::nullopt;
        session_uuid_ = std::nullopt;
        socket_.close();
    }

    bool Client::Talker::IsConnected() const {
        return connected_;
    }

    void Client::Connect(const ip::tcp::endpoint &ep) {
        talker_.Connect(ep);
    }

    Client::Talker::Talker() : socket_(service_), already_read_(0), buff_() {}

    void Client::Talker::Connect(const ip::tcp::endpoint &ep) try {
        socket_.connect(ep);
        connected_ = true;
    } catch (const boost::exception &e) {
        std::cout << "Can't connect to server" << std::endl;
        return;
    }

    void Client::Talker::TryDoRequest() {
        if (!connected_) {
            return;
        }
        mutex_.lock();
        ++id_transaction_;
        mutex_.unlock();

        auto request = talk_helper::MakeRequest(id_transaction_, session_uuid_,
                                                login_);
        if (request.is_stop) {
            return Disconnect();
        }
        if (request.login) {
            possible_login_ = request.login;
        }
        if (request.message) {
            DoWrite(*request.message);
            return;
        }
        return TryDoRequest(); // tail recursion
    }

    [[maybe_unused]] std::string Client::Talker::GetLogin() const {
        if (!login_) {
            return "";
        }
        return *login_;
    }

    void Client::Talker::TryRead() {
        if (!connected_) {
            return;
        }
        mutex_.lock();
        try {
            already_read_ = 0;
            read(socket_, buffer(buff_),
                 boost::bind(&Client::Talker::IsReadComplete, this, _1, _2));
        } catch (...) {
            Disconnect();
            mutex_.unlock();
            return;
        }
        if (ParseResponse()) {
            mutex_.unlock();
            return TryRead(); // tail recursion
        }
        mutex_.unlock();

    }

    bool Client::Talker::ParseResponse() {
        if ((already_read_ < 1) || (buff_[0] != '{')) {
            return true;
        }
        std::string message_serv(buff_, already_read_);
        if (message_serv.empty()) {
            return false;
        }
        auto response = talk_helper::ParseResponse(message_serv,
                                                   is_response_print_);
        if (response.session_uuid) {
            session_uuid_ = response.session_uuid;
            login_ = possible_login_;
        }
        if (!response.is_connected) {
            Disconnect();
            return false;
        }
        if (response.is_message) {
            return true;
        }
        return false;
    }

    void Client::Talker::DoWrite(const std::string &msg) {
        if (msg.empty() || !connected_) {
            return;
        }
        mutex_.lock();
        try {
            socket_.write_some(buffer(msg));
        } catch (...) {
            Disconnect();
        }
        mutex_.unlock();
    }

    size_t Client::Talker::IsReadComplete(const boost::system::error_code &err,
                                          size_t bytes) {
        if (err) {
            return 0;
        }
        already_read_ = bytes;

        if (already_read_ && (buff_[0] != '{')) {
            return 0;
        }

        size_t left = std::count(buff_, buff_ + bytes, '{');
        size_t right = std::count(buff_, buff_ + bytes, '}');
        bool found = left == right && left != 0;

        return found ? 0 : 1;
    }

} // namespace client
