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

#include "server_info.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <limits>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

// ---------------------------------------------------------
//                      Helper Functions
// ---------------------------------------------------------

namespace {

    using json = nlohmann::json;

    /**
     * @brief Get the IP from the environment variable or use the default.
     *
     * @return std::string_view The ip
     */
    std::string_view getEnvIP() {
        if (const char *ipEnv = std::getenv(config::ENV_VAR_IP.data())) {
            return ipEnv;
        }

        return config::DEFAULT_IP;
    }

    /**
     * @brief Get the port from the environment variable or use the default.
     *
     * @return uint16_t The port
     */
    static uint16_t getEnvPort() {
        const char *portEnv = std::getenv(config::ENV_VAR_PORT.data());
        if (!portEnv) {
            return config::DEFAULT_PORT;
        }

        try {
            int port = std::stoi(portEnv);
            if (port >= std::numeric_limits<uint16_t>::min()
                && port <= std::numeric_limits<uint16_t>::max()) {
                return static_cast<uint16_t>(port);
            }
        } catch (...) {
        }

        return config::DEFAULT_PORT;
    }

    /**
     * @brief Create the directory data and the config.json file if they don't
     * exist.
     */
    void createDirAndConfigFile() {
        std::filesystem::path path(config::getConfigPath());
        std::filesystem::create_directories(path.parent_path());

        bool writeDefault = false;

        if (!std::filesystem::exists(path)) {
            writeDefault = true;
        } else if (std::filesystem::is_regular_file(path)
                   && std::filesystem::file_size(path) == 0) {
            writeDefault = true;
        }

        // Write default config file if it doesn't exist
        if (writeDefault) {
            json j;
            j["server"]["ip"] = getEnvIP();
            j["server"]["port"] = getEnvPort();

            std::ofstream file(config::getConfigPath());
            if (file) {
                file << j.dump(4);
            }
            file.close();
        }
    }

} // namespace

// ---------------------------------------------------------
//                      Public API
// ---------------------------------------------------------

namespace config {

    using json = nlohmann::json;

    void saveServerInfo(const ServerInfo &serverInfo) {
        createDirAndConfigFile();

        json j;

        std::ifstream readFile(getConfigPath());
        if (readFile) {
            try {
                readFile >> j;
            } catch (...) {
            }
        }

        j["server"]["ip"] = serverInfo.ip;
        j["server"]["port"] = serverInfo.port;

        std::ofstream writeFile(getConfigPath());
        if (!writeFile) {
            return;
        }

        writeFile << j.dump(4);
        writeFile.close();
    }

    ServerInfo loadServerInfo() {
        createDirAndConfigFile();

        ServerInfo serverInfo;

        try {
            std::ifstream file(getConfigPath());
            if (!file) {
                serverInfo.ip = getEnvIP();
                serverInfo.port = getEnvPort();
                return serverInfo;
            }

            json j;
            file >> j;
            file.close();

            serverInfo.ip = j["server"]["ip"].get<std::string>();
            serverInfo.port = j["server"]["port"].get<uint16_t>();

        } catch (...) {
            serverInfo.ip = getEnvIP();
            serverInfo.port = getEnvPort();
        }

        return serverInfo;
    }

    std::string getConfigPath() {
    #ifdef _WIN32
        const char* appdata = std::getenv("APPDATA");
        if (!appdata) throw std::runtime_error("APPDATA not set");
        return std::string(appdata) + "\\royal-blocks\\data\\config.json";
    #elif defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
        const char* home = std::getenv("HOME");
        if (!home) throw std::runtime_error("HOME not set");
        return std::string(home) + "/.config/royal-blocks/data/config.json";
    #else
        throw std::runtime_error("Unsupported OS");
    #endif
    }

} // namespace config
