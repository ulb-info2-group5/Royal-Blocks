#include "client.hpp"


int main(){
    try{
        boost::asio::io_context io;
        TcpClient client(io, "127.0.0.1", "1234");
        io.run();
    }catch(std::exception& e){
        std::cerr << "execption : " << e.what() << std::endl;
    }

    return 0;
}