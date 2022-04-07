#include <string>
#include <unordered_map>
#include <boost/uuid/uuid.hpp>

namespace json_config::request {

    enum Command {
        kHello,
        kLogin,
        kMessage,
        kPing,
        kRegister,
        kLogOut,
        kHelp,
        kStop,
        kNoSuchCommand,
        kLogOutReply,
        kMessageReply,
        kPingReply,
    };

    namespace {

        const std::unordered_map<Command, std::string> kCommandMap = {
                {kHello,         "HELLO"},
                {kLogin,         "login"},
                {kMessage,       "message"},
                {kPing,          "ping"},
                {kRegister,      "register"},
                {kLogOut,        "logout"},
                {kStop,          "stop"},
                {kHelp,          "help"},
                {kNoSuchCommand, "no_such_command"},
                {kLogOutReply,   "logout_reply"},
                {kMessageReply,  "message_reply"},
                {kPingReply,     "ping_reply"},
        };

        const std::unordered_map<std::string, Command> kCommandMapReversed = {
                {"HELLO",           kHello},
                {"login",           kLogin},
                {"message",         kMessage},
                {"ping",            kPing},
                {"register",        kRegister},
                {"stop",            kStop},
                {"help",            kHelp},
                {"logout",          kLogOut},
                {"no_such_command", kNoSuchCommand},
                {"logout_reply",    kLogOutReply},
                {"message_reply",   kMessageReply},
                {"ping_reply",      kPingReply},
        };

    } // namespace

    std::string CommandAsString(Command command) {
        try {
            return kCommandMap.at(command);
        } catch (const std::out_of_range &e) {
            return "no_such_command";
        }
    }

    Command CommandFromString(const std::string &command) {
        try {
            return kCommandMapReversed.at(command);
        } catch (const std::out_of_range &e) {
            return kNoSuchCommand;
        }
    }

    struct Request {
        int id;
        Command command;
    };

    struct RequestAuthorization : public Request {
        std::string login, password;
    };

    struct RequestSendMessage : public Request {
        std::string body;
        std::string session_uuid;
    };

    struct RequestSendMessageFromServer : public RequestSendMessage {
        std::string sender_login;
    };

    struct RequestPing : public Request {
        std::string session_uuid;
    };

    typedef RequestPing RequestLogOut;
    typedef RequestAuthorization RequestRegister;
    typedef Request RequestHello;

} // namespace include::request