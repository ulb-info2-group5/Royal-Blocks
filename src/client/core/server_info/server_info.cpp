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
        std::filesystem::path path(config::CONFIG_PATH);
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

            std::ofstream file(config::CONFIG_PATH.data());
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

        std::ifstream readFile(CONFIG_PATH.data());
        if (readFile) {
            try {
                readFile >> j;
            } catch (...) {
            }
        }

        j["server"]["ip"] = serverInfo.ip;
        j["server"]["port"] = serverInfo.port;

        std::ofstream writeFile(CONFIG_PATH.data());
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
            std::ifstream file(CONFIG_PATH.data());
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

} // namespace config
