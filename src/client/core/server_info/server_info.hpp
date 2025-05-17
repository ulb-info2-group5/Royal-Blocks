/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

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
