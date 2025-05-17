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

#include "tetris_main_server.hpp"

#include "../database/database_manager/database_manager.hpp"
#include "network/network.hpp"

/*Publics methods*/

uint16_t TetrisMainServer::getEnvPort() {
    if (const char *port_env = std::getenv(ENV_VAR_PORT)) {
        try {
            return std::stoi(port_env);
        } catch (...) {
            std::cerr << noServerPortVariable << std::endl;
        }
    }
    return DEFAULT_PORT;
}
TetrisMainServer *TetrisMainServer::instance_ = nullptr;

uint16_t TetrisMainServer::handleArguments(int argc, char *argv[]) {
    if (argc > 2) {
        throw std::invalid_argument(invalidNumberOfArguments);
    }

    if (argc == 1) {
        return getEnvPort();
    }

    std::string arg = argv[1];

    if (arg == "--help") {
        std::cout << help << std::endl;
        std::exit(0);
    }

    try {
        int port = std::stoi(arg);
        if (port < 1 || port > std::numeric_limits<uint16_t>::max()) {
            throw std::invalid_argument(invalidPortRange);
        }
        return static_cast<uint16_t>(port);
    } catch (...) {
        throw std::invalid_argument(invalidPortType);
    }
}

TetrisMainServer::TetrisMainServer(int argc, char *argv[])
    : dbManager(std::make_shared<DatabaseManager>()),
      database{std::make_shared<AccountManager>(dbManager),
               std::make_shared<FriendsManager>(dbManager),
               std::make_shared<MessagesManager>(dbManager)},
      clientManager(database), serverPort(handleArguments(argc, argv)) {
    instance_ = this;
}
void TetrisMainServer::handler(const boost::system::error_code &error,
                               int /*signal_number*/) {
    if (!error) {
        instance_->getClientManager().shutdown();
        exit(1);
    }
}

void TetrisMainServer::run() {
    try {
        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        Network network(io_context, clientManager, serverPort);
        std::cout << "Server started on port " << serverPort << std::endl;
        signals.async_wait(handler);
        io_context.run();

    } catch (std::exception &e) {
        std::cerr << "Exception : " << e.what() << std::endl;
    }
}

ClientManager &TetrisMainServer::getClientManager() { return clientManager; }