#include "server_info.hpp"

#include <cstdint>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace config {
    using json = nlohmann::json;

    void saveServerInfo(const ServerInfo& serverInfo) {
        createDirAndConfigFile();

        json j;
        j["server"]["ip"] = serverInfo.ip;
        j["server"]["port"] = serverInfo.port;

        std::ofstream file(CONFIG_PATH);
        if (!file) {
            std::cerr << "Error when trying to open the 'config' file." << std::endl;
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
            std::ifstream file(CONFIG_PATH);
            if (!file) {
                return serverInfo;
            }         

            json j;
            file >> j;
            file.close();

            serverInfo.ip = j["server"]["ip"].get<std::string>();
            serverInfo.port = j["server"]["port"].get<uint16_t>();

        } catch (const std::exception& e) {
            std::cerr << "Error reading config file: " << e.what() << std::endl;
        }

        return serverInfo;
    }

    static void createDirAndConfigFile() {
        std::filesystem::path path(CONFIG_PATH);
        std::filesystem::create_directories(path.parent_path());

        // Write default config file if it doesn't exist
        if (!std::filesystem::exists(path)) {
            json j;
            j["server"]["ip"] = getEnvIP();
            j["server"]["port"] = getEnvPort();
    
            std::ofstream file(CONFIG_PATH);
            if (file) {
                file << j.dump(4);
            }
            file.close();
        }
    }
    
    static std::string getEnvIP() {
        if (const char* ip_env = std::getenv(ENV_VAR_IP)) {
            return ip_env;
        }
        return DEFAULT_IP;
    }

    static uint16_t getEnvPort() {
        if (const char* port_env = std::getenv(ENV_VAR_PORT)) {
            try {
                return std::stoi(port_env);
            } catch (...) {
                std::cerr << "Invalid SERVER_PORT environment variable, using default." << std::endl;
            }
        }
        return DEFAULT_PORT;
    }
}