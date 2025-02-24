#include "network.hpp"

int main()
{
    try
    {
        boost::asio::io_context io_context;
        Network network(io_context);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception : " << e.what() << std::endl;
    }

    return 0;
}
