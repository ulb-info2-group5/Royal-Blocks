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

#include "network.hpp"

#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/impl/scheduler.ipp>
#include <boost/asio/detail/impl/service_registry.hpp>
#include <boost/asio/execution/context_as.hpp>
#include <boost/asio/execution/prefer_only.hpp>
#include <boost/asio/impl/execution_context.hpp>
#include <boost/asio/impl/io_context.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/detail/impl/endpoint.ipp>
#include <boost/system/detail/error_code.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string>
#include <utility>

#include "../../common/types/types.hpp"
#include "../client_link/client_link.hpp"
#include "../client_manager/client_manager.hpp"

using json = nlohmann::json;

using boost::asio::ip::tcp;

// ====== Network class ======

//--- private ---
void Network::accept() {
    acceptor_.async_accept([this](boost::system::error_code ec,
                                  tcp::socket socket) {
        if (!ec) {

            std::shared_ptr<ClientLink> newLink = std::make_shared<ClientLink>(
                std::move(socket),
                [this](const std::string &packet, const int clientId) {
                    clientManager_.handlePacket(packet, clientId);
                },
                [this](nlohmann::json binding) -> nlohmann::json {
                    return clientManager_.authPacketHandler(binding).value();
                },
                [this](std::shared_ptr<ClientLink> clientLink,
                       nlohmann::json clientData) {
                    clientManager_.authSuccessCall(clientLink, clientData);
                },
                [this](std::optional<UserID> userID) {
                    clientManager_.removeClient(userID);
                });

            clientManager_.addClientInWaitingForAuth(std::move(newLink));
        }
        accept();
    });
}

// --- public ---
Network::Network(boost::asio::io_context &io, ClientManager &clientManager,
                 uint16_t port)
    : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), port)),
      clientManager_(clientManager) {
    this->accept();
}
