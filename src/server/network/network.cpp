
#include "network.hpp"

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
                    return clientManager_.authPacketHandler(binding);
                },
                [this](std::shared_ptr<ClientLink> clientLink,
                       nlohmann::json clientData) {
                    clientManager_.authSuccessCall(clientLink, clientData);
                },
                [this](std::optional<UserID> userID){
                    clientManager_.removeClient(userID);
                });

            clientManager_.addClientInWaitingForAuth(std::move(newLink));
        }
        accept();
    });
}

// --- public ---
Network::Network(boost::asio::io_context &io, ClientManager &clientManager, uint16_t port)
    : io_(io), acceptor_(io, tcp::endpoint(tcp::v4(), port)),
      clientManager_(clientManager) {
    this->accept();
}
