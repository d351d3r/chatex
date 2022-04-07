#include <boost/thread/mutex.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "Response.hpp"

namespace server {
    class Server;
} // namespace server


namespace storages {

    class UsersTable {
    private:
        std::unordered_map<std::string, std::string> users_;
        boost::mutex mutex_;

        friend server::Server;

    public:
        json_config::response::Response
        InsertUser(const std::string &login, const std::string &password);

        json_config::response::Response
        IsPasswordCorrect(const std::string &login, const std::string &password);

        json_config::response::Response
        EraseUser(const std::string &login, const std::string &password);

        size_t Size() const;
    };

    class MessageTable {
    private:
        std::unordered_map<int, std::string> table_messages_;
        std::unordered_map<std::string, std::vector<int>> table_unreaded_messages_;
        boost::mutex mutex_;
        int max_id_ = 0;

    public:
        int InsertMessage(const std::string &message);

        json_config::response::Response
        InsertReciever(int id, const std::string &login_reciever);

        std::vector<int> PopReciever(const std::string &login_reciever);

        std::string FindMessageById(int id);

        int IncreaseMaxId();
    };

} // namespace storages