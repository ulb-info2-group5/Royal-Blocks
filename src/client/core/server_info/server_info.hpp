#ifndef SERVER_INFO_HPP
#define SERVER_INFO_HPP

#include <cstdint>
#include <string>
#include <string_view>

namespace config {

    inline constexpr uint16_t DEFAULT_PORT = 1234;
    inline const std::string_view DEFAULT_IP = "127.0.0.1";
    inline const std::string_view ENV_VAR_IP = "SERVER_IP";
    inline const std::string_view ENV_VAR_PORT = "SERVER_PORT";
    inline const std::string_view CONFIG_PATH = "data/config.json";

    struct ServerInfo {
        std::string ip;
        uint16_t port;
    };

    void saveServerInfo(const ServerInfo &serverInfo);

    /**
     * @brief Returns the server info.
     */
    ServerInfo loadServerInfo();

} // namespace config

#endif // SERVER_INFO_HPP
