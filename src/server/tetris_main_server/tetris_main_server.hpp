#ifndef TETRIS_MAIN_SERVER_HPP
#define TETRIS_MAIN_SERVER_HPP

#include <boost/asio/impl/io_context.ipp>    
#include <boost/asio/io_context.hpp>         
#include <boost/system/detail/error_code.hpp>
#include <cstdint>                           
#include <memory>                            

#include "../client_manager/client_manager.hpp" 

class DatabaseManager;

constexpr uint16_t DEFAULT_PORT = 1234;
constexpr char ENV_VAR_PORT[] = "SERVER_PORT";

constexpr char invalidNumberOfArguments[] = "\033[1;31merror:\033[0m invalid number of arguments\nTry './tetris_royal_server --help' for more information.";
constexpr char noServerPortVariable[] = "No SERVER_PORT environment variable set. Using default.";
constexpr char invalidPortRange[] = "Port must be between 1 and 65535.";
constexpr char invalidPortType[] = "Port must be a number between 1 and 65535.";
constexpr char help[] = "Tetris Royal Server : Help\n\nUsage: ./tetris_royal_server [port]\nport: The port to listen on (default: 1234)";

/**
 * @class
 *
 * @brief
 */
class TetrisMainServer{
    private:
        std::shared_ptr<DatabaseManager> dbManager;
        DataBase database;
        ClientManager clientManager;
        boost::asio::io_context io_context;
        uint16_t serverPort ;

    public:
        /**
        * @brief Construct a new Tetris Main Server object
        */
        TetrisMainServer(int argc , char * argv[]);

        /**
         * @brief Destroy the Tetris Main Server object
         */
        ~TetrisMainServer() = default;

        static TetrisMainServer* instance_;

        /**
        * @brief run server
        */
        void run();
        static void handler(const boost::system::error_code& error,int signal_number);
        

        /**
         * @brief Get the port from the environment variable or use the default
         *
         * @return uint16_t The port choice for the server
         */
        uint16_t getEnvPort();

        /**
         * @brief Handle the arguments passed to the program
         *
         * @param argc The number of arguments
         * @param argv The arguments
         * @return uint16_t The port choice for the server
         */
        uint16_t handleArguments(int argc, char *argv[]);


        ClientManager& getClientManager();

};

#endif // TETRIS_MAIN_SERVER_HPP