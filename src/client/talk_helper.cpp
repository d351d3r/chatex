#include "headers/talk_helper.hpp"

#include <iostream>

#include "json.hpp"
#include "Request.hpp"
#include "parcer_helper.hpp"
#include "Response.hpp"

namespace talk_helper {

    namespace {
        using namespace json_config;
        using namespace json_config::request;
        using Json = nlohmann::json;

        const std::string kBadRequestAsString = "bad request";
        const std::vector<std::string> kKeysForParsingStrings = {"command", "status",
                                                                 "message", "session"};
        const std::vector<std::string> kKeysForParsingInts = {"id", "client_id"};
        const size_t min_password_length = 4;

        Request WriteCommandList() {
            std::cout
                    << "'HELLO' - command use to hello server. No need to other fields\n"
                       "'register' - register into server. Need login and password\n"
                       "'login' - log in. Need login and password\n"
                       "'logout' - log out. No need to other fields\n"
                       "'message' - send message to other users. Need message, optional"
                       " sender login\n"
                       "'ping' - ping server (don't print answer). No need to other fields\n"
                       "'stop' - stop client. No need to other fields\n"
                       "'help' - list of commands. No need to other fields" << std::endl;
            return {};
        }

        Request MakeLoginRequest(const Command &command, int id) {
            std::string login, password;
            std::cout << "Write login" << std::endl;
            std::cin >> login;
            int counter_bad_requests = 0;
            while ((password.size() < min_password_length) &&
                   ((++counter_bad_requests) < 5)) {
                std::cout << "Write password at least " << min_password_length << " symbols"
                          << std::endl;
                std::cin >> password;
            }
            if (password.size() < min_password_length) {
                std::cout << "To many bad requests" << std::endl;
                return {};
            }
            Request request = {(Json{{"id",       id},
                                     {"command",  CommandAsString(command)},
                                     {"login",    login},
                                     {"password", password}}.dump())};
            if (command == json_config::request::kLogin) {
                request.login = login;
            }
            return request;
        }

        Request
        MakeMessageRequest(int id, const std::optional<std::string> &session_uuid,
                           const std::optional<std::string> &login) {
            if (!session_uuid) {
                std::cout << "You should login before you send message" << std::endl;
                return {};
            }
            std::string message, message_part_2;
            char ans;
            std::cout << "Write your message in one line" << std::endl;
            std::cin >> message;
            std::getline(std::cin, message_part_2);
            message += message_part_2;
            std::cout << "Do you want to add your login? (y/n)" << std::endl;
            std::cin >> ans;

            if (ans == 'y') {
                if (!login) {
                    std::cout << "There no login. Sending without login? (y/n)" << std::endl;
                    std::cin >> ans;
                    if (ans == 'n') {
                        return {};
                    }
                } else {
                    return {(Json{{"id",           id},
                                  {"command",      "message"},
                                  {"body",         message},
                                  {"session",      *session_uuid},
                                  {"sender_login", *login}}.dump())};
                }
            }
            return {(Json{{"id",      id},
                          {"command", "message"},
                          {"body",    message},
                          {"session", *session_uuid}}.dump())};
        }

        Request MakeHelloRequest(int id) {
            return {(Json{{"id",      id},
                          {"command", "HELLO"}}.dump())};
        }

        void ParseMessage(const Json &answer) {
            if (auto command = parcer_helper::ParseString(answer, "command")) {
                return;
            }
            auto message = parcer_helper::ParseString(answer, "message");
            if (!message) {
                return;
            }
            std::cout << "You got message";
            if (auto sender_login = parcer_helper::ParseString(answer, "sender_login")) {
                std::cout << " from " << *sender_login;
            }
            std::cout << ": " << *message << std::endl;
        }

        std::optional<std::string> MakeStringFromKeys(const Json &answer) {
            std::string out;
            for (const auto &key: kKeysForParsingStrings) {
                if (auto value = parcer_helper::ParseString(answer, key)) {
                    out += "  " + key + ": '" + *value + "'\n";
                }
                if (out.empty()) {
                    return {};
                }
            }
            for (const auto &key: kKeysForParsingInts) {
                if (auto value = parcer_helper::ParseInt(answer, key)) {
                    out += "  " + key + ": '" + std::to_string(*value) + "'\n";
                }
            }
            return "Response:\n" + out;
        }

        bool IsLogout(const Json &answer) {
            if (auto command = parcer_helper::ParseString(answer, "command")) {
                if (CommandFromString(*command) == kLogOutReply) {
                    if (auto status = parcer_helper::ParseString(answer, "status")) {
                        if (response::Response{response::kOk}.AsString() == *status) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        bool IsGoodPing(const Json &answer) {
            if (auto command = parcer_helper::ParseString(answer, "command")) {
                if (CommandFromString(*command) == kPingReply) {
                    if (auto status = parcer_helper::ParseString(answer, "status")) {
                        if (response::Response{response::kOk}.AsString() == *status) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        Response ParseCommand(const Json &answer, bool is_print) {
            Response response;
            if (IsGoodPing(answer)) {
                response.is_message = false;
                return response;
            }
            if (auto out = MakeStringFromKeys(answer)) {
                response.is_message = false;
                if (is_print) {
                    std::cout << *out;
                }
            }
            if (auto session_uuid = parcer_helper::ParseString(answer, "session")) {
                // successfully login if session returned
                response.session_uuid = session_uuid;
            }
            response.is_connected = IsLogout(answer);

            return response;
        }

    } // namespace

    Request MakePingRequest(const std::string &command, int id,
                            const std::optional<std::string> &session_uuid) {
        if (!session_uuid) {
            std::cout << "You should login before you log out" << std::endl;
            return {};
        }
        return {(Json{{"id",      id},
                      {"command", command},
                      {"session", *session_uuid}}.dump())};
    }

    Request MakeRequest(int id, const std::optional<std::string> &session_uuid,
                        const std::optional<std::string> &login) {
        std::string command_as_string;
        Request request;
        std::cout << "Write command ('help' to get command list)" << std::endl;
        std::cin >> command_as_string;
        auto command = CommandFromString(command_as_string);
        switch (command) {
            case kRegister:
            case kLogin:
                return MakeLoginRequest(command, id);
            case kMessage:
                return MakeMessageRequest(id, session_uuid, login);
            case kPing:
            case kLogOut:
                return MakePingRequest(CommandAsString(command), id, session_uuid);
            case kStop:
                return {std::nullopt, std::nullopt, true};
            case kHello:
                return MakeHelloRequest(id);
            case kHelp:
                WriteCommandList();
                break;
            default:
                std::cout << "No such command" << std::endl;
        }
        return {};
    }

    Response ParseResponse(const std::string &response, bool is_print) {
        Json answer;
        try {
            answer = Json::parse(response);
        } catch (const nlohmann::detail::parse_error &ex) {}
        ParseMessage(answer);
        return ParseCommand(answer, is_print);
    }

} // namespace talk_helper
