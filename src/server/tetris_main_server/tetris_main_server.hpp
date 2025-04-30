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

class TetrisMainServer{
    private:
        /*std::shared_ptr<DatabaseManager> dbManager = std::make_shared<DatabaseManager>();
        DataBase database{std::make_shared<AccountManager>(dbManager),
                    std::make_shared<FriendsManager>(dbManager),
                    std::make_shared<MessagesManager>(dbManager)};

        ClientManager clientManager(database);

        boost::asio::io_context io_context;*/

        std::shared_ptr<DatabaseManager> dbManager;
        DataBase database;
        ClientManager clientManager;
        boost::asio::io_context io_context;

    public:
        /*
        * @brief Construct a new Tetris Main Server object
        */
        TetrisMainServer(int argc, char* argv[]);

        /*
         * @brief Destroy the Tetris Main Server object
         */
        ~TetrisMainServer() = default;

        void run();

        /*
         * @brief Get the port from the environment variable or use the default
         *
         * @return uint16_t The port choice for the server
         */
        uint16_t getEnvPort();

        /*
         * @brief Handle the arguments passed to the program
         *
         * @param argc The number of arguments
         * @param argv The arguments
         * @return uint16_t The port choice for the server
         */
        uint16_t handleArguments(int argc, char *argv[]);

};