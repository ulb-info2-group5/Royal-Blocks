
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


void ClientLink::start(){
    std::cout << "start client link" << std::endl;
}



// ====== Client manager class ======
// ---private ---



// ---public ---
ClientManager::ClientManager(DataBase database) : database_(database) {
    std::cout << "clientManager construct" << std::endl;
}


void ClientManager::addConnection(int clientId, std::shared_ptr<ClientLink> clientSession){
    std::lock_guard<std::mutex> lock(mutex_);
    connectedClients_[clientId] = clientSession;

}

void ClientManager::handlePacket(const std::string& packet){
    std::cout << "-- handle Packet call -- " <<std::endl;
}


bool ClientManager::checkCredentials(const std::string& pseudo, const std::string& password){
    if (!database_.accountManager->checkUsernameExists(pseudo)){
        std::cout << "username false" << std::endl;
        return false;
    }else{
        if (database_.accountManager->checkUserPassword(pseudo, password)){
            return true;
        }else {
            std::cout <<  "password false" << std::endl;
            return false; 
        }
    }
}
