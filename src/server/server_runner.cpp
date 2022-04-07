#include "Server.hpp"

constexpr static int kPort = 8080;

int main() {
    boost::shared_ptr<server::Server> server_ptr(new server::Server(kPort));
    server_ptr->Start();
}
