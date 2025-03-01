#include "client.hpp"


int main(){

    boost::asio::io_context io;
    TcpClient client(io, "127.0.0.1", "1234");
    client.askForAuthentication();
    
    std::thread t([&io]() { io.run(); });

    std::string user_input;
    
    while (std::getline(std::cin, user_input)) {
        client.sendMessage(user_input + "\n");
    }
    io.stop();
    t.join();

    return 0;
}