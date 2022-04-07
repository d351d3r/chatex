#include "Server.hpp"

constexpr static int port = 8080;

int main() {
    boost::shared_ptr<server::Server> server_ptr(new server::Server(port));
    server_ptr->Start();
}
