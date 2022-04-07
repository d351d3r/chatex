#include "storages.hpp"

namespace storages {

    namespace {
        using namespace json_config::response;
    } // namespace

    size_t UsersTable::Size() const {
        return users_.size();
    }

    Response
    UsersTable::InsertUser(const std::string &login, const std::string &password) {
        if (login.empty()) {
            return {kBadRequest};
        }
        mutex_.lock();
        if (users_.count(login)) {
            mutex_.unlock();
            return {kStateMismatch};
        }
        users_[login] = password;
        mutex_.unlock();
        return {kOk};
    }

    Response UsersTable::IsPasswordCorrect(const std::string &login,
                                           const std::string &password) {
        if (login.empty()) {
            return {kBadRequest};
        }
        mutex_.lock();
        if (!users_.count(login)) {
            mutex_.unlock();
            return {kNotFound};
        }
        if (users_.at(login) != password) {
            mutex_.unlock();
            return {kStateMismatch};
        }
        mutex_.unlock();
        return {kOk};
    }

    Response
    UsersTable::EraseUser(const std::string &login, const std::string &password) {
        if (login.empty()) {
            return {kBadRequest};
        }
        mutex_.lock();
        if (!users_.count(login)) {
            mutex_.unlock();
            return {kNotFound};
        }
        if (users_.at(login) != password) {
            mutex_.unlock();
            return {kStateMismatch};
        }
        users_.erase(login);
        mutex_.unlock();
        return {kOk};
    }

    int MessageTable::InsertMessage(const std::string &message) {
        mutex_.lock();
        table_messages_[max_id_++] = message;
        int res = max_id_ - 1;
        mutex_.unlock();
        return res;
    }

    Response
    MessageTable::InsertReciever(int id, const std::string &login_reciever) {
        if (login_reciever.empty()) {
            return {kBadRequest};
        }
        mutex_.lock();
        if (!table_messages_.count(id)) {
            mutex_.unlock();
            return {kNotFound};
        }
        if (!table_unreaded_messages_.count(login_reciever)) {
            table_unreaded_messages_[login_reciever] = {id};
            mutex_.unlock();
            return {kOk};
        }
        table_unreaded_messages_[login_reciever].push_back(id);
        mutex_.unlock();
        return {kOk};
    }

    std::vector<int> MessageTable::PopReciever(const std::string &login_reciever) {
        if (login_reciever.empty()) {
            return {kBadRequest};
        }
        mutex_.lock();
        if (!table_unreaded_messages_.count(login_reciever)) {
            mutex_.unlock();
            return {};
        }
        auto res = table_unreaded_messages_[login_reciever];
        table_unreaded_messages_.erase(login_reciever);
        mutex_.unlock();
        return res;
    }

    std::string MessageTable::FindMessageById(int id) {
        mutex_.lock();
        if (!table_messages_.count(id)) {
            mutex_.unlock();
            return "";
        }
        mutex_.unlock();
        return table_messages_.at(id);
    }

    int MessageTable::IncreaseMaxId() {
        mutex_.lock();
        ++max_id_;
        int res = max_id_ - 1;
        mutex_.unlock();
        return res;
    }

} // namespace storages