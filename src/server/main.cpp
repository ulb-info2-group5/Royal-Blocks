#include "network/network.hpp"

int main() {
   
 
    auto dbManager = std::make_shared<DatabaseManager>();
    DataBase database{std::make_shared<AccountManager>(dbManager),
                      std::make_shared<FriendsManager>(dbManager),
                      std::make_shared<MessagesManager>(dbManager)};
    // database.accountManager->createAccount("leo", "leo");

    ClientManager clientManager(database);
    try {
        boost::asio::io_context io_context;
        Network network(io_context, clientManager);
        io_context.run();
    } catch (std::exception &e) {
        std::cerr << "Exception : " << e.what() << std::endl;
    }

    return 0;
}
