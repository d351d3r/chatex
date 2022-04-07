#pragma once

#include <string>
#include <unordered_map>

namespace json_config::response {

    enum MessageCode {
        kOk = 200,
        kBadRequest = 400,
        kUnauthorized = 401,
        kForbidden = 403,
        kNotFound = 404,
        kStateMismatch = 409,
        kGone = 410,
        kServerError = 500,
    };

    namespace {

        const std::unordered_map<MessageCode, std::string> MessageMap = {
                {kOk,            "ok"},
                {kBadRequest,    "bad request"},
                {kUnauthorized,  "unauthorized"},
                {kForbidden,     "forbidden"},
                {kNotFound,      "not found"},
                {kStateMismatch, "state mismatch"},
                {kGone,          "gone"},
                {kServerError,   "internal server error"}
        };

    } // namespace

    struct Response {
        MessageCode status = kOk;

        std::string AsString() const {
            try {
                return MessageMap.at(status);
            } catch (const std::out_of_range &e) {
                return MessageMap.at(kServerError);
            }
        }
    };

} // namespace include::Response
