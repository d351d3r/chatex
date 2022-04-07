#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

#include "json.hpp"

#include "storages.hpp"

namespace server {

    class Server;

    class Server : public boost::enable_shared_from_this<Server> {
    public:
        class ClientTalker;

        typedef boost::shared_ptr<ClientTalker> ClientPtr;
        typedef boost::system::error_code ErrorCode;
        typedef boost::asio::ip::tcp::acceptor Acceptor;
        typedef boost::asio::ip::tcp::socket Socket;
        using Json = nlohmann::json;

        static const int kBufferSize = 1024;

        explicit Server(size_t port);

        void Start();

        boost::asio::io_service &GetService();

        void AddClient(const ClientPtr &client);

        void RemoveClient(const ClientPtr &client);

        json_config::response::Response
        InsertUser(const std::string &login, const std::string &password);

        json_config::response::Response
        IsPasswordCorrect(const std::string &login, const std::string &password);

        json_config::response::Response
        EraseUser(const std::string &login, const std::string &password);

        class ClientTalker
                : public boost::enable_shared_from_this<ClientTalker>,
                  boost::asio::noncopyable {
        public:
            explicit ClientTalker(boost::shared_ptr<Server> server);

            static ClientPtr NewClient(boost::shared_ptr<Server> server);

            void Start();

            void Stop();

            bool IsStarted() const;

            Socket &GetSocket();

            std::string GetUsername() const;

            json_config::response::Response
            LogIn(const std::string &, const std::string &);

            std::string GetSessionUuid() const;

            int DoWriteToAllOtherClients(const std::string &);

            void DoWriteAllUnreadedMesseges();

            json_config::response::Response
            InsertUser(const std::string &login, const std::string &password);

            json_config::response::Response
            IsPasswordCorrect(const std::string &login, const std::string &password);

            json_config::response::Response
            EraseUser(const std::string &login, const std::string &password);

            void DoWrite(const std::string &message);

            void DoWriteWothoutRead(const std::string &message);

            bool IsAuthorizated() const;

        private:
            boost::shared_ptr<Server> my_server_;
            Socket socket_;
            bool started_{};
            char read_buffer_[kBufferSize]{};
            char write_buffer_[kBufferSize]{};
            std::string session_uuid_;
            std::string login_;
            boost::mutex mutex_;

            void OnRead(const ErrorCode &error, size_t bytes_count);

            void DoRead();

            size_t IsReadComplete(const ErrorCode &error, size_t bytes_count);

            void ParseMessage(const std::string &message);

            void OnWrite(const ErrorCode &error, size_t bytes_count);
        };

    private:
        boost::asio::io_service service_;
        Acceptor acceptor_;
        std::vector<ClientPtr> clients_;
        storages::UsersTable user_table_;
        storages::MessageTable message_table_;

        void AcceptHandler(const ClientPtr &client, const ErrorCode &error);
    };

} // namespace server
