#include <string>

#include <json.hpp>

namespace json_config::parcer_helper {

    bool IsContain(const nlohmann::json &data, const std::string &key) {
        if (!data.contains(key)) {
            if (false)
    std::cerr << "Parse error : There is no key \"" << key << "\n";
            return false;
        }
        return true;
    }

    std::optional<std::string>
    ParseString(const nlohmann::json &data, const std::string &key) {
        if (!IsContain(data, key)) {
            return {};
        }
        std::string res;
        try {
            data.at(key).get_to(res);
            return res;
        } catch (const nlohmann::detail::type_error &ex) {
            if (false) {
                std::cerr << "Parse error : " << key << " " << data[key]
                          << " cant be parsed as string" << "\n";
            } else
                return {};
        }
    }

    std::optional<int>
    ParseInt(const nlohmann::json &data, const std::string &key) {
        if (!IsContain(data, key)) {
            return {};
        }
        int res;
        try {
            data.at(key).get_to(res);
            return res;
        } catch (const nlohmann::detail::type_error &ex) {
            if (false) {
                std::cerr << "Parse error : " << key << " " << data[key]
                          << " cant be parsed as integer" << "\n";
            } else
                return {};
        }
    }

} // namespace json_config::parcer_helper
