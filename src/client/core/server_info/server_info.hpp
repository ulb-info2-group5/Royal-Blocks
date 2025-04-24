#ifndef SERVER_INFO_HPP
#define SERVER_INFO_HPP

#include <cstdint>
#include <string>

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 1234
#define CONFIG_PATH "data/config.json"
#define ENV_VAR_IP "SERVER_IP"
#define ENV_VAR_PORT "SERVER_PORT"

namespace config {

    struct ServerInfo {
        std::string ip;
        uint16_t port;
    };

    void saveServerInfo(const ServerInfo &serverInfo);

    ServerInfo loadServerInfo();

    /*
    * @brief Create the directory data and the config.json file if they don't exist
    */
    static void createDirAndConfigFile();

    /*
    * @brief Get the IP from the environment variable or use the default
    *
    * @return std::string The IP
    */
    static std::string getEnvIP();

    /*
    * @brief Get the port from the environment variable or use the default
    *
    * @return uint16_t The port
    */
    static uint16_t getEnvPort();
}

#endif // SERVER_INFO_HPP