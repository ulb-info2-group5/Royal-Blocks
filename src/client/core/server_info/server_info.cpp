#include "server_info.hpp"

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
        serverInfo.ip = DEFAULT_IP;
        serverInfo.port = DEFAULT_PORT;

        json j;

        std::ifstream file(CONFIG_PATH);
        if (!file) {    // If the file doesn't exist, we use default values or env vars if set
            if (const char* ip_env = std::getenv(ENV_VAR_IP)) {
                serverInfo.ip = ip_env;
            }
            if (const char* port_env = std::getenv(ENV_VAR_PORT)) {
                try {
                    serverInfo.port = std::stoi(port_env);
                } catch (...) {
                    std::cerr << "Invalid SERVER_PORT environment variable, using default." << std::endl;
                }
            }
            return serverInfo;
        }

        file >> j;
        file.close();

        serverInfo.ip = j["server"]["ip"].get<std::string>();
        serverInfo.port = j["server"]["port"].get<int>();

        return serverInfo;
    }

    void createDirAndConfigFile() {
        std::filesystem::path path(CONFIG_PATH);
        std::filesystem::create_directories(path.parent_path());

        if (!std::filesystem::exists(path)) {
            std::ofstream file(CONFIG_PATH);
            file.close();
        }
    }
}