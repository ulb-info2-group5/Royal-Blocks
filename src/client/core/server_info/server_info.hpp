#ifndef SERVER_INFO_HPP
#define SERVER_INFO_HPP

#include <string>

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 1234
#define CONFIG_PATH "data/config.json"
#define ENV_VAR_IP "SERVER_IP"
#define ENV_VAR_PORT "SERVER_PORT"

namespace config {

    struct ServerInfo {
        std::string ip;
        int port;
    };

    void saveServerInfo(const ServerInfo &serverInfo);

    ServerInfo loadServerInfo();

    /*
    * @brief Create the directory data if it doesn't exist
    */
    void createDirAndConfigFile();

}

#endif // SERVER_INFO_HPP