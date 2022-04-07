#pragma once

#include <Response.hpp>

#include "Server.hpp"

namespace replies {

json_config::response::Response
ManageMessage(const nlohmann::json &, const server::Server::ClientPtr&);

} // namespace replies
