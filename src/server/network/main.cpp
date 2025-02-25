#include "network.hpp"

int main()
{
    ClientManager clientManager;
    try{
        boost::asio::io_context io_context;
        Network network(io_context, clientManager);
        io_context.run();
    }
    catch (std::exception& e){
        std::cerr << "Exception : " << e.what() << std::endl;
    }
    return 0;
}
