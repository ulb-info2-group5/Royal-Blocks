#include "client_link.hpp"



// ====== tcp connection class ======

// --- private ---

void ClientLink::read() {
    boost::asio::async_read_until(
        socket_, streamBuffer_, '\n',
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                handleReading();
            } else if (ec == boost::asio::error::eof) {
                handleErrorReading();
            }
        });
}

void ClientLink::handleReading() {
    std::istream is(&streamBuffer_);
    std::string packet;
    std::getline(is, packet);
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
    nlohmann::json removeClient = bindings::RemoveClient{}.to_json();
    if (getUserState() == bindings::State::Offline) {
        mustBeDeletedFromTheWaitingForAuthList_ = false;
        authPacketHandler_(removeClient.at("type").get<bindings::BindingType>(),
                           removeClient);
    }else if (getUserState() == bindings::State::InGame){
        packetHandler_(bindings::QuitGame{}.to_json().dump(), clientId.value());
        setUserState(bindings::State::Offline);
        packetHandler_(removeClient.dump(), clientId.value());
    } 
    
    else {
        packetHandler_(removeClient.dump(), clientId.value());
    }
}

void ClientLink::handleAuthentication(std::string &packet) {
    nlohmann::json jsonPacket = nlohmann::json::parse(packet);
    nlohmann::json response =
        authPacketHandler_(jsonPacket.at("type").get<bindings::BindingType>(),
                           jsonPacket.at("data"));
    sendPackage(response);
    std::cout << response.dump() << std::endl;
    if (response.at("type").get<bindings::BindingType>()
            == bindings::BindingType::AuthenticationResponse
        && response.at("data").at("success").get<bool>()) {
        authSuccessCallback_(shared_from_this(), jsonPacket.at("data"));
        userState = bindings::State::Menu;
        mustBeDeletedFromTheWaitingForAuthList_ = true;
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
                       AuthSuccessCallback authSuccessCallback)
    : socket_(std::move(socket)), userState(bindings::State::Offline),
      clientId(std::nullopt),gameMode_(std::nullopt), packetHandler_(packetHandler),
      authPacketHandler_(authPacketHandler),
      authSuccessCallback_(authSuccessCallback) {
    start();
}

void ClientLink::start() {
    std::cout << "start client link" << std::endl;
    read();
}

void ClientLink::jointGame(const std::weak_ptr<GameServer>& gameServer){
    pGame_ = gameServer;
}


bool ClientLink::shouldItBeDeletedFromTheList() {
    return mustBeDeletedFromTheWaitingForAuthList_;
}

void ClientLink::sendPackage(nlohmann::json gameState) {
    buffer_ = gameState.dump() + "\n";
    std::cout << "package send : " << gameState.dump() << std::endl;
    writeSocket(buffer_);
}

void ClientLink::setClientId(const int id) { clientId = id; }

void ClientLink::setUserState(bindings::State newState) {
    userState = newState;
}
void ClientLink::setGameMode(GameMode newGameMode){
    gameMode_ = newGameMode;
}

std::optional<GameMode> ClientLink::getGameMode(){
    return gameMode_;
}

bindings::State ClientLink::getUserState() { return userState; }

UserID ClientLink::getUserID(){
    return clientId.value();
}
