
#include "client_manager.hpp"


using json = nlohmann::json;


using boost::asio::ip::tcp;



// ====== tcp connection class ======


// --- private ---

void ClientLink::read(){
    boost::asio::async_read_until(socket_, streamBuffer_, '\n',[this](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            
            std::istream is(&streamBuffer_);
            std::string packet;
            std::getline(is, packet);
            std::cout << "packet : " << packet << std::endl;
            if (!identify_) {
                handleAuthentication(packet);
            }else {
                packetHandler_(packet);
            }
            read();
        }
    }); 
}

void ClientLink::handleAuthentication(std::string & packet){
    nlohmann::json jsonPacket = nlohmann::json::parse(packet);
    nlohmann::json response = authPacketHandler_(jsonPacket.at("type").get<bindings::BindingType>(),jsonPacket.at("data"));
    sendResponse(response);
    std::cout << response.dump() << std::endl;
    if (response.at("type").get<bindings::BindingType>() == bindings::BindingType::AuthenticationResponse){
        authSuccessCallback_(shared_from_this(), jsonPacket.at("data"));
        identify_ = true;
    }
}

void ClientLink::writeSocket(std::string &content){
    boost::asio::async_write(socket_, boost::asio::buffer(content) , [this](boost::system::error_code ec, std::size_t length){
        if (!ec){
            std::cout << "message send from the server " << std::endl;
            buffer_.erase(0, length);
        }
    });
}

// --- public ---
ClientLink::ClientLink(tcp::socket socket, PacketHandler packetHandler, AuthPacketHandler authPacketHandler, AuthSuccessCallback authSuccessCallback) 
: socket_(std::move(socket)), packetHandler_(packetHandler), authPacketHandler_(authPacketHandler), authSuccessCallback_(authSuccessCallback) {
    start();
}


void ClientLink::start(){
    std::cout << "start client link" << std::endl;
    read();
}

bool ClientLink::isIdentify(){
    return identify_;
}

void ClientLink::recieveMessage( const std::string & content){
    nlohmann::json j;
    //j["senderId"] = senderId ;
    j["content"] = content;
    buffer_ = j.dump() + "\n";
    writeSocket(buffer_);
}

void ClientLink::sendResponse(nlohmann::json response){
    buffer_ = response.dump() + "\n";
    writeSocket(buffer_);
}


// ====== Client manager class ======
// ---private ---



void ClientManager::removeAuthClients(){
    auto ne = remove_if(waitingForAuthClient.begin(), waitingForAuthClient.end(),
    [](std::shared_ptr<ClientLink> x) {
      return x->isIdentify();
    });
    waitingForAuthClient.erase(ne, waitingForAuthClient.end());
}

// ---public ---
ClientManager::ClientManager(DataBase database) : database_(database) {
}


void ClientManager::authSuccessCall(std::shared_ptr<ClientLink> clientLink, nlohmann::json clientData){
    addConnection(clientLink, clientData.at("nickname").get<std::string>());
}


void ClientManager::addConnection(std::shared_ptr<ClientLink> clientSession, const std::string& pseudo){
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "new client id :" << database_.accountManager->getUserId(pseudo) << std::endl;  
    connectedClients_[database_.accountManager->getUserId(pseudo)] = clientSession;
    removeAuthClients();
}



nlohmann::json ClientManager::authPacketHandler(bindings::BindingType type, nlohmann::json data){
    nlohmann::json response;
    switch (type){
    case bindings::BindingType::Authentication :
        if (checkCredentials(data)){
            response = bindings::AuthenticationResponse{true}.to_json();
        }
        break;
    case bindings::BindingType::Registration :
        // TODO : create a new compte and ask for login
        break;
    default:
        break;
    }
    return response;
}



void ClientManager::handlePacket(const std::string& packet){
    nlohmann::json jPack = nlohmann::json::parse(packet);
    std::cout << "-- handle Packet call -- " <<std::endl;
    bindings::BindingType type = jPack.at("type").get<bindings::BindingType>();
    nlohmann::json data = jPack.at("data").get<nlohmann::json>();

    switch (type)
    {
    case bindings::BindingType::Message:  
        handleMessage(data);
        break;
    default:
        break;
    }
}

void ClientManager::addClientInWaitingForAuth(std::shared_ptr<ClientLink> clientLink){
    waitingForAuthClient.push_back(clientLink);
}

void ClientManager::handleMessage(nlohmann::json message){
    std::cout << message.at("content").get<std::string>() << std::endl;
    std::lock_guard<std::mutex> lock(mutex_);
    connectedClients_[message.at("recipientId").get<int>()]->recieveMessage(message.at("content").get<std::string>());
    

}


bool ClientManager::checkCredentials(nlohmann::json data ){
    if (!database_.accountManager->checkUsernameExists(data.at("nickname").get<std::string>())){
        std::cout << "username false" << std::endl;    
        return false;
    }else{
        if (database_.accountManager->checkUserPassword(data.at("nickname").get<std::string>(), data.at("password").get<std::string>())){
            return true;
        }else {
            std::cout <<  "password false" << std::endl;
            return false; 
        }
    }
}
