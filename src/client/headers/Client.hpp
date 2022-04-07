#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <string>

namespace client {

    class Client {
    public:
        Client();

        void Connect(const boost::asio::ip::tcp::endpoint &);

        void Run(bool is_response_print = true);

        class Talker {
        public:
            bool is_response_print_ = true;

            Talker();

            void Connect(const boost::asio::ip::tcp::endpoint &);

            void TryDoRequest();

            void TryRead();

            void Disconnect();

            void DoPing();

            [[maybe_unused]] [[nodiscard]] std::string GetLogin() const;

            [[nodiscard]] bool IsConnected() const;

            [[nodiscard]] bool IsLogedIn() const;

        private:
            bool ParseResponse();

            void DoWrite(const std::string &msg);

            size_t IsReadComplete(const boost::system::error_code &err, size_t bytes);

            bool connected_ = false;
            int id_transaction_ = 0;
            enum {
                max_msg = 1024
            };
            boost::asio::io_service service_;
            boost::asio::ip::tcp::socket socket_;
            size_t already_read_;
            char buff_[max_msg];
            std::optional<std::string> login_;
            std::optional<std::string> session_uuid_;
            std::optional<std::string> possible_login_;
            boost::mutex mutex_;
        };

    private:
        void RunPing();

        Talker talker_;
    };
} // namespace client
