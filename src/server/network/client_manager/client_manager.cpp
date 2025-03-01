
#include "client_manager.hpp"


using json = nlohmann::json;


using boost::asio::ip::tcp;



// ====== tcp connection class ======


// --- private ---

void ClientLink::read(){
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(buffer_), '\n',[this](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout << "packet:  " << buffer_ << std::endl;
            
            if (buffer_ != "\n") packetHandler_(buffer_);
            buffer_.erase(0, length);
        }
        read();
    }); 
}



// --- public ---
ClientLink::ClientLink(tcp::socket socket, std::function<void (const std::string& )> packetHandler) 
: socket_(std::move(socket)), packetHandler_(packetHandler) {

}


void ClientLink::start(){
    std::cout << "start client link" << std::endl;
    read();
}

void ClientLink::recieveMessage( const std::string & content){
    nlohmann::json j;
    //j["senderId"] = senderId ;
    j["content"] = content;
    buffer_ = j.dump() + "\n";
    boost::asio::async_write(socket_, boost::asio::buffer(buffer_) , [this](boost::system::error_code ec, std::size_t length){
        if (!ec){
            std::cout << "message send from the server " << std::endl;
            buffer_.erase(0, length);
        }

    });
}


// ====== Client manager class ======
// ---private ---



// ---public ---
ClientManager::ClientManager(DataBase database) : database_(database) {
}


void ClientManager::addConnection(std::shared_ptr<ClientLink> clientSession, const std::string& pseudo){
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "new client id :" << database_.accountManager->getUserId(pseudo) << std::endl;  
    connectedClients_[database_.accountManager->getUserId(pseudo)] = clientSession;
    clientSession->start();
}

void ClientManager::handlePacket(const std::string& packet){

    std::cout << "-- handle Packet call -- " <<std::endl;
    nlohmann::json jPack = nlohmann::json::parse(packet);
    char type = jPack.at("type").get<char>();
    switch (type)
    {
    case MESSAGE:  
        handleMessage(jPack);
        break;
    
    default:
        break;
    }
}

void ClientManager::handleMessage(nlohmann::json message){
    std::cout << message.at("content").get<std::string>() << std::endl;
    std::lock_guard<std::mutex> lock(mutex_);
    connectedClients_[message.at("receiverId").get<int>()]->recieveMessage(message.at("content").get<std::string>());
    

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
