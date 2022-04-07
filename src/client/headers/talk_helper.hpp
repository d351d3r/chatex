#include <optional>
#include <string>

namespace talk_helper {

    struct Request {
        std::optional<std::string> message;
        std::optional<std::string> login;
        bool is_stop = false;
    };

    struct Response {
        std::optional<std::string> session_uuid;
        bool is_message = true;
        bool is_connected = true;
    };

    Request MakePingRequest(const std::string &command, int id,
                            const std::optional<std::string> &session_uuid);

    Request MakeRequest(int id, const std::optional<std::string> &session_uuid,
                        const std::optional<std::string> &login);

    Response ParseResponse(const std::string &response, bool is_print = true);

} // namespace talk_helper
