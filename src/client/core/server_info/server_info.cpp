#include "server_info.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <nlohmann/json.hpp>

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

        std::cerr << config::ENV_VAR_IP
                  << " environment variable not set.Using default."
                  << std::endl;

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
            std::cerr << config::ENV_VAR_PORT
                      << " environment variable not set. Using default."
                      << std::endl;
            return config::DEFAULT_PORT;
        }

        try {
            int port = std::stoi(portEnv);
            if (port >= std::numeric_limits<uint16_t>::min()
                && port <= std::numeric_limits<uint16_t>::max()) {
                return static_cast<uint16_t>(port);
            } else {
                std::cerr << config::ENV_VAR_PORT
                          << " out of valid range [0, 65535]. Using "
                             "default."
                          << std::endl;
            }
        } catch (...) {
            std::cerr << "Invalid " << config::ENV_VAR_PORT
                      << " value. Using default." << std::endl;
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

        // Write default config file if it doesn't exist
        if (!std::filesystem::exists(path)) {
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
        j["server"]["ip"] = serverInfo.ip;
        j["server"]["port"] = serverInfo.port;

        std::ofstream file(CONFIG_PATH.data());
        if (!file) {
            std::cerr << "Error when trying to open the 'config' file."
                      << std::endl;
            return;
        }

        file << j.dump(4);
        file.close();
    }

    ServerInfo loadServerInfo() {
        createDirAndConfigFile();

        ServerInfo serverInfo;
        serverInfo.ip = getEnvIP();
        serverInfo.port = getEnvPort();

        try {
            std::ifstream file(CONFIG_PATH.data());
            if (!file) {
                return serverInfo;
            }

            json j;
            file >> j;
            file.close();

            serverInfo.ip = j["server"]["ip"].get<std::string>();
            serverInfo.port = j["server"]["port"].get<uint16_t>();

        } catch (const std::exception &e) {
            std::cerr << "Error reading config file: " << e.what() << std::endl;
        }

        return serverInfo;
    }

} // namespace config
