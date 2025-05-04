#include "client_link.hpp"

#include "../../common/bindings/constants.hpp"

#include <iostream>

// ====== tcp connection class ======

// --- private ---

void ClientLink::read() {
    boost::asio::async_read_until(
        socket_, streamBuffer_, bindings::PACKET_DELIMITER,
        [this](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                
                handleReading();
            } else if (ec == boost::asio::error::eof) {
                handleErrorReading();
            }
        });
}

bool ClientLink::checkPackage(std::string& package){

    nlohmann::json checkJson;
    try{
        checkJson =  nlohmann::json::parse(package);
    }catch(nlohmann::json::parse_error& e){
        std::cerr << "Received packet is not valid JSON: " << e.what()<< std::endl;
        return false ;
    }

    try {
        checkJson.at("type").get<bindings::BindingType>();
    }catch(nlohmann::json::exception& e){
        std::cerr <<"Received packet has no type  : " << e.what() << std::endl;
        return false;
    }

    return true;
}

void ClientLink::handleReading() {
    std::istream is(&streamBuffer_);
    std::string packet;
    std::getline(is, packet);
    //check if the package has the correct format
    if (!checkPackage(packet)) {
        return;
    }
    std::cout << "packet : " << packet << std::endl;
    if (getUserState() == bindings::State::Offline) {
        handleAuthentication(packet);
    } else {
        packetHandler_(packet, clientId.value());
    }
    read();
}

void ClientLink::handleErrorReading() {
    std::cout << "erreor reading " << std::endl;
    mustBeDeletedFromTheWaitingForAuthList_ = true;
    removeClientCallback_(clientId);
}

void ClientLink::handleAuthentication(std::string &packet) {

    nlohmann::json jsonPacket  = nlohmann::json::parse(packet);
    std::optional<nlohmann::json> response = authPacketHandler_(jsonPacket);
    if (response&& !(response->is_null())){
        sendPackage(response.value());
        std::cout << response.value().dump() << std::endl;

        if (response.value().at(bindings::PACKET_TYPE_FIELD).get<bindings::BindingType>()== bindings::BindingType::AuthenticationResponse
            && response.value().at("data").at("success").get<bool>()) {
            authSuccessCallback_(shared_from_this(), jsonPacket.at("data"));
            userState = bindings::State::Menu;
            mustBeDeletedFromTheWaitingForAuthList_ = true;
        }
    }
    
}

void ClientLink::writeSocket(std::string &content) {
    boost::asio::async_write(
        socket_, boost::asio::buffer(content),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "message send from the server " << std::endl;
                buffer_.erase(0, length);
            }
        });
}

// --- public ---
ClientLink::ClientLink(tcp::socket socket, PacketHandler packetHandler,
                       AuthPacketHandler authPacketHandler,
                       AuthSuccessCallback authSuccessCallback,
                       RemoveClientCallback removeClientCallback)
    : socket_(std::move(socket)), userState(bindings::State::Offline),
      clientId(std::nullopt), gameMode_(std::nullopt),
      packetHandler_(packetHandler), authPacketHandler_(authPacketHandler),
      authSuccessCallback_(authSuccessCallback),
      removeClientCallback_(removeClientCallback) {
    start();
}

void ClientLink::start() {
    std::cout << "start client link" << std::endl;
    read();
}

void ClientLink::jointGame(const std::weak_ptr<GameServer> &gameServer) {
    pGame_ = gameServer;
}

void ClientLink::exitGame() {
    setUserState(bindings::State::Menu);
    setGameMode(std::nullopt);
    resetGame();
}

void ClientLink::resetGame() { pGame_.reset(); }

bool ClientLink::shouldItBeDeletedFromTheList() {
    return mustBeDeletedFromTheWaitingForAuthList_;
}

void ClientLink::sendPackage(nlohmann::json gameState) {
    buffer_ = gameState.dump().append(bindings::PACKET_DELIMITER);

    std::cout << static_cast<int>(userState) << "\n" << std::endl;
    std::cout << gameState << std::endl;

    writeSocket(buffer_);
}

void ClientLink::setClientId(const int id) { clientId = id; }

void ClientLink::setUserState(bindings::State newState) {
    userState = newState;
}
void ClientLink::setGameMode(std::optional<GameMode> newGameMode) {
    gameMode_ = newGameMode;
}

std::optional<GameMode> ClientLink::getGameMode() { return gameMode_; }

bindings::State ClientLink::getUserState() { return userState; }

UserID ClientLink::getUserID() { return clientId.value(); }

std::weak_ptr<GameServer> ClientLink::getGameServer() { return pGame_; }
