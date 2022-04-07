#include "Server.hpp"

#include <boost/bind.hpp>
#include <utility>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <algorithm>
#include <unordered_set>

#include "replies.hpp"

using namespace boost::asio;

namespace server {

    namespace {
        using namespace json_config;
    } // namespace

    Server::Server(size_t port)
            : service_(), acceptor_(service_, ip::tcp::endpoint(ip::tcp::v4(), port)),
              clients_() {
        std::cout << "Server start on host : " << boost::asio::ip::host_name()
                  << ", port : " << port << std::endl;
    }

    void Server::Start() {
        ClientPtr client = ClientTalker::NewClient(shared_from_this());
        acceptor_.async_accept(client->GetSocket(),
                               boost::bind(&Server::AcceptHandler, shared_from_this(),
                                           client, _1));
        service_.run();
    }

    response::Response
    Server::InsertUser(const std::string &login, const std::string &password) {
        return user_table_.InsertUser(login, password);
    }

    response::Response Server::IsPasswordCorrect(const std::string &login,
                                                 const std::string &password) {
        return user_table_.IsPasswordCorrect(login, password);
    }

    response::Response
    Server::EraseUser(const std::string &login, const std::string &password) {
        return user_table_.EraseUser(login, password);
    }

    Server::Socket &Server::ClientTalker::GetSocket() { return socket_; }

    void Server::AcceptHandler(const ClientPtr &client, const ErrorCode &error) {
        client->Start();
        ClientPtr new_clinet = ClientTalker::NewClient(shared_from_this());
        acceptor_.async_accept(new_clinet->GetSocket(),
                               boost::bind(&Server::AcceptHandler, shared_from_this(),
                                           new_clinet, _1));
    }

    io_service &Server::GetService() { return service_; }

    void Server::AddClient(const ClientPtr &client) { clients_.push_back(client); }

    void Server::RemoveClient(const ClientPtr &client) {
        clients_.erase(std::find(clients_.begin(), clients_.end(), client));
    }

    Server::ClientTalker::ClientTalker(boost::shared_ptr<Server> server)
            : my_server_(std::move(std::move(server))), socket_(my_server_->GetService()) {
        session_uuid_ = to_string(boost::uuids::random_generator()());
    }

    std::string Server::ClientTalker::GetSessionUuid() const {
        return session_uuid_;
    }

    void Server::ClientTalker::Start() {
        std::cout << "Client added" << std::endl;
        started_ = true;
        my_server_->AddClient(shared_from_this());
        DoRead();
    }

    bool Server::ClientTalker::IsStarted() const {
        return started_;
    }

    Server::ClientPtr
    Server::ClientTalker::NewClient(boost::shared_ptr<Server> server) {
        ClientPtr ptr(new ClientTalker(std::move(server)));
        return ptr;
    }

    void Server::ClientTalker::DoRead() {
        async_read(socket_, buffer(read_buffer_),
                   boost::bind(&Server::ClientTalker::IsReadComplete,
                               shared_from_this(), _1, _2),
                   boost::bind(&Server::ClientTalker::OnRead, shared_from_this(), _1,
                               _2));
    }

    size_t Server::ClientTalker::IsReadComplete(const ErrorCode &error,
                                                size_t bytes_count) {
        if (error) {
            return 0;
        }

        size_t left = std::count(read_buffer_, read_buffer_ + bytes_count, '{');
        size_t right = std::count(read_buffer_, read_buffer_ + bytes_count, '}');
        bool found = left == right && left != 0;

        return found ? 0 : 1;
    }

    void Server::ClientTalker::OnRead(const ErrorCode &error, size_t bytes_count) {
        if (error) {
            Stop();
        }
        if (!started_) {
            return;
        }

        std::string message(read_buffer_, bytes_count);
        ParseMessage(message);
    }

    void Server::ClientTalker::Stop() {
        if (!started_) {
            return;
        }
        started_ = false;
        socket_.close();
        std::cout << "Client stoped" << std::endl;
        my_server_->RemoveClient(shared_from_this());
    }

    void Server::ClientTalker::ParseMessage(const std::string &message) {
        std::cout << "Got message : " << message << std::endl;
        Json input;
        try {
            input = Json::parse(message);
        } catch (const nlohmann::detail::parse_error &ex) {
            std::cerr << "Parse error: " << ex.what() << std::endl;
        }
        replies::ManageMessage(input, shared_from_this());
    }

    void Server::ClientTalker::DoWrite(const std::string &message) {
        if (!started_) {
            return;
        }
        mutex_.lock();
        std::cout << "send message : " << message << std::endl;
        std::copy(message.begin(), message.end(), write_buffer_);
        socket_.async_write_some(buffer(write_buffer_),
                                 boost::bind(&Server::ClientTalker::OnWrite,
                                             shared_from_this(), _1, _2));
        mutex_.unlock();
    }

    void Server::ClientTalker::DoWriteWothoutRead(const std::string &message) {
        if (!started_) {
            return;
        }
        mutex_.lock();
        std::cout << "send message : " << message << std::endl;
        std::copy(message.begin(), message.end(), write_buffer_);
        socket_.write_some(buffer(write_buffer_));
        mutex_.unlock();
    }

    std::string Server::ClientTalker::GetUsername() const {
        return login_;
    }

    response::Response Server::ClientTalker::LogIn(const std::string &login,
                                                   const std::string &password) {
        if (!login_.empty()) {
            return {response::kStateMismatch};
        }
        auto response = IsPasswordCorrect(login, password);
        if (response.status != response::kOk) {
            return response;
        }
        login_ = login;
        std::cout << "login_ = " << login_ << std::endl;
        return {response::kOk};
    }

    void Server::ClientTalker::OnWrite(const ErrorCode &error, size_t bytes_count) {
        DoRead();
    }

    response::Response Server::ClientTalker::InsertUser(const std::string &login,
                                                        const std::string &password) {
        return my_server_->InsertUser(login, password);
    }

    response::Response
    Server::ClientTalker::IsPasswordCorrect(const std::string &login,
                                            const std::string &password) {
        return my_server_->IsPasswordCorrect(login, password);
    }

    response::Response Server::ClientTalker::EraseUser(const std::string &login,
                                                       const std::string &password) {
        return my_server_->EraseUser(login, password);
    }

    void Server::ClientTalker::DoWriteAllUnreadedMesseges() {
        if (login_.empty()) {
            return;
        }
        auto unread_messages = my_server_->message_table_.PopReciever(login_);
        for (auto message: unread_messages) {
            DoWriteWothoutRead(my_server_->message_table_.FindMessageById(message));
        }
    }

    int Server::ClientTalker::DoWriteToAllOtherClients(const std::string &message) {
        std::unordered_set<std::string> logins_recived;
        for (auto &client: my_server_->clients_) {
            if (client->login_ == login_) {
                continue;
            }
            logins_recived.insert(client->login_);
            client->DoWriteWothoutRead(message);
        }
        if (my_server_->user_table_.Size() <= logins_recived.size() + 1) {
            return my_server_->message_table_.IncreaseMaxId();
        }
        int id = my_server_->message_table_.InsertMessage(message);
        for (const auto &login: my_server_->user_table_.users_) {
            if (login.first == login_ || logins_recived.count(login.first)) {
                continue;
            }
            my_server_->message_table_.InsertReciever(id, login.first);
        }
        return id;
    }

    bool Server::ClientTalker::IsAuthorizated() const {
        return !login_.empty();
    }

} // namespace server
