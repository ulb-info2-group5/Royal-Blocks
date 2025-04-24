#include "database/database_manager/database_manager.hpp"
#include "network/network.hpp"
#include <cstdint>
#include <memory>

constexpr uint16_t DEFAULT_PORT = 1234;
constexpr char ENV_VAR_PORT[] = "SERVER_PORT";

constexpr char invalidNumberOfArguments[] = "\033[1;31merror:\033[0m invalid number of arguments\nTry './tetris_royal_server --help' for more information.";
constexpr char noServerPortVariable[] = "No SERVER_PORT environment variable set. Using default.";
constexpr char invalidPortRange[] = "Port must be between 1 and 65535.";
constexpr char invalidPortType[] = "Port must be a number between 1 and 65535.";
constexpr char help[] = "Tetris Royal Server : Help\n\nUsage: ./tetris_royal_server [port]\nport: The port to listen on (default: 1234)";

/*
 * @brief Get the port from the environment variable or use the default
 *
 * @return uint16_t The port choice for the server
 */
uint16_t getEnvPort() {
    if (const char* port_env = std::getenv(ENV_VAR_PORT)) {
        try {
            return std::stoi(port_env);
        } catch (...) {
            std::cerr << noServerPortVariable << std::endl;
        }
    }
    return DEFAULT_PORT;
}

/*
 * @brief Handle the arguments passed to the program
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return uint16_t The port choice for the server
 */
uint16_t handleArguments(int argc, char *argv[]) {
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

int main(int argc, char *argv[]) {
    try {
        uint16_t port = handleArguments(argc, argv);

        std::shared_ptr<DatabaseManager> dbManager = std::make_shared<DatabaseManager>();
        DataBase database{std::make_shared<AccountManager>(dbManager),
                    std::make_shared<FriendsManager>(dbManager),
                    std::make_shared<MessagesManager>(dbManager)};

        ClientManager clientManager(database);

        boost::asio::io_context io_context;
        Network network(io_context, clientManager, port);
        std::cout << "Server started on port " << port << std::endl;
        io_context.run();
    } catch (std::exception &e) {
        std::cerr << "Exception : " << e.what() << std::endl;
    }

    return 0;
}