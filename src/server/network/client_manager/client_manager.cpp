
#include "client_manager.hpp"


using json = nlohmann::json;


using boost::asio::ip::tcp;



// ====== tcp connection class ======


// --- private ---

void ClientLink::read(){
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(buffer_), '\n',[this](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout << "packet:  " << this->buffer_ << std::endl;
            read();
        }
    }); 
}


// --- public ---
ClientLink::ClientLink(tcp::socket socket, std::function<void (const std::string& )> packetHandler) 
: socket_(std::move(socket)), packetHandler_(packetHandler) {

}


// ====== Client manager class ======
// ---private ---



// ---public ---
void ClientManager::addConnection(int clientId, std::shared_ptr<ClientLink> clientSession){
    std::lock_guard<std::mutex> lock(mutex_);
    connectedClients_[clientId] = clientSession;

}

void ClientManager::handlePacket(const std::string& packet){
    std::cout << "-- handle Packet call -- " <<std::endl;
}
