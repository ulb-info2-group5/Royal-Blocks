#include "tetris_main_server.hpp"

/*Publics methods*/

uint16_t TetrisMainServer::getEnvPort() {
    if (const char* port_env = std::getenv(ENV_VAR_PORT)) {
        try {
            return std::stoi(port_env);
        } catch (...) {
            std::cerr << noServerPortVariable << std::endl;
        }
    }
    return DEFAULT_PORT;
}
TetrisMainServer* TetrisMainServer::instance_ = nullptr;

uint16_t TetrisMainServer::handleArguments(int argc, char *argv[]) {
    if (argc > 2) {
        throw std::invalid_argument(invalidNumberOfArguments);
    }

    if (argc == 1) {
        return getEnvPort();
    }

    std::string arg = argv[1];

    if (arg == "--help") {
        std::cout << help << std::endl;
        std::exit(0);
    }

    try {
        int port = std::stoi(arg);
        if (port < 1 || port > std::numeric_limits<uint16_t>::max()) {
            throw std::invalid_argument(invalidPortRange);
        }
        return static_cast<uint16_t>(port);
    } catch (...) {
        throw std::invalid_argument(invalidPortType);
    }
}

TetrisMainServer::TetrisMainServer(int argc , char* argv[]) : 
    dbManager(std::make_shared<DatabaseManager>()),
    database{
        std::make_shared<AccountManager>(dbManager),
        std::make_shared<FriendsManager>(dbManager),
        std::make_shared<MessagesManager>(dbManager)},
    clientManager(database), 
    serverPort(handleArguments(argc, argv))
    {
    instance_ = this;
}
void TetrisMainServer::handler(const boost::system::error_code& error , int signal_number){
    
    if (!error){
        std::cout << "a signal occurred" << std::endl;    
        instance_->getClientManager().shutdown();
        exit(1);
    }
}


void TetrisMainServer::run(){
    try {
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        Network network(io_context, clientManager, serverPort);
        std::cout << "Server started on port " << serverPort << std::endl;
        signals.async_wait(handler);
        io_context.run();
        
        
    } catch (std::exception &e) {
        std::cerr << "Exception : " << e.what() << std::endl;
    }
}

ClientManager& TetrisMainServer::getClientManager(){
    return clientManager;
}