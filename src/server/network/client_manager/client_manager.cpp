
#include "client_manager.hpp"

#include "../../../common/bindings/ranking.hpp"

#include <bcrypt.h>

using json = nlohmann::json;

using boost::asio::ip::tcp;

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

// ====== Client manager class ======
// ---private ---

void ClientManager::removeClientsFromTheWaintingList() {
    auto ne =
        remove_if(waitingForAuthClient.begin(), waitingForAuthClient.end(),
                  [](std::shared_ptr<ClientLink> x) {
                      return x->shouldItBeDeletedFromTheList();
                  });
    waitingForAuthClient.erase(ne, waitingForAuthClient.end());

}

bool ClientManager::attemptCreateAccount(nlohmann::json data) {
    const std::string username = data.at("nickname").get<std::string>();
    const std::string password = data.at("password").get<std::string>();

    // Hash the password before storing it for better security
    std::string hash = bcrypt::generateHash(password);

    CreateAccountStatus status = database_.accountManager->createAccount(username, hash);
    if (status == CreateAccountStatus::SUCCESS) return true;
    return false;
}

void ClientManager::disconnectClient(const UserID &userID) {
    if (!isClientConnected(userID)) {
        std::cout << "the client has already been disconnected id : "<< userID << std::endl;
    } else {

        connectedClients_[userID]->setUserState(bindings::State::Offline);
        addClientInWaitingForAuth(std::move(connectedClients_[userID]));
        removeConnection(userID);
    }
}

void ClientManager::removeConnection(const UserID &userID) {
    std::cout << "remove connection call " << std::endl;
    connectedClients_.erase(userID);
}

void ClientManager::sendUpdatedRankingToClients() const {
    std::vector<std::pair<std::string, size_t>> ranking = database_.accountManager->getRanking();
    nlohmann::json rankingJson = bindings::Ranking{ranking}.to_json();
    for (auto &client : connectedClients_) {
        client.second->sendPackage(rankingJson);
    }
}


// ---public ---
ClientManager::ClientManager(DataBase database)
    : database_(database),
    gamesManager_(
        [this](PlayerID playerId, nlohmann::json gameState) {
            updateGamePlayer(playerId, gameState);
        },
        [this](UserID user, int score) {
            database_.accountManager->updateScore(user, score);
        },
        [this]() {
            sendUpdatedRankingToClients();
        }),
    matchmaking_(
        [this](std::vector<UserID> userIDs, std::shared_ptr<GameServer> gameServer) { gameFindCallback(userIDs, gameServer); }), 

    socialService_(database.friendsManager, database.messagesManager, 
        [this](UserID userID)->bindings::User { return getUser(userID) ; })
     {}




void ClientManager::authSuccessCall(std::shared_ptr<ClientLink> clientLink,
                                    nlohmann::json clientData) {
    addConnection(clientLink, clientData.at("nickname").get<std::string>());
    std::vector<std::pair<std::string, size_t>> ranking = database_.accountManager->getRanking();
    nlohmann::json rankingJson = bindings::Ranking{ranking}.to_json();
    clientLink->sendPackage(rankingJson);
    
    

}
void ClientManager::gameFindCallback(std::vector<PlayerID> &playersID, std::shared_ptr<GameServer> gameServer) {
    std::cout << "== game find callback succcess ===" << std::endl;
    
    for (auto id : playersID) {
        std::cout << "id player : " << id << std::endl;
        connectedClients_[id]->setUserState(bindings::State::InGame);
        connectedClients_[id]->jointGame(gameServer);
        gamesManager_.makeClientJoinGame(connectedClients_[id], gameServer);
    }
}

void ClientManager::addConnection(std::shared_ptr<ClientLink> clientSession,
                                  const std::string &pseudo) {
    std::lock_guard<std::mutex> lock(mutex_);
    const UserID id = database_.accountManager->getUserId(pseudo);
    std::cout << "new client id :" << id << std::endl;
    clientSession->setClientId(id);
    connectedClients_[id] = clientSession;
    removeClientsFromTheWaintingList();
    connectedClients_[id]->setUserState(bindings::State::Menu);
    updateMenu(id);
    
}

nlohmann::json ClientManager::authPacketHandler(bindings::BindingType type,
                                                nlohmann::json data) {
    nlohmann::json response;
    switch (type) {
    case bindings::BindingType::Authentication:
        response = (checkCredentials(data))
                       ? bindings::AuthenticationResponse{true}.to_json()
                       : bindings::AuthenticationResponse{false}.to_json();
        break;
    case bindings::BindingType::Registration:
        response = (attemptCreateAccount(data))
                       ? bindings::RegistrationResponse{true}.to_json()
                       : bindings::RegistrationResponse{false}.to_json();
        break;
    case bindings::BindingType::RemoveClient:
        removeClientsFromTheWaintingList();
    default:
        break;
    }
    return response;
}

void ClientManager::handlePacket(const std::string &packet,
                                 const UserID &clientId) {

    if (connectedClients_[clientId]->getUserState() == bindings::State::InGame ) {

        gamesManager_.enqueueGameBinding(clientId, packet);
        return;
    } else {
        handlePacketMenu(std::move(packet), std::move(clientId));
    }
}




void ClientManager::handlePacketMenu(const std::string &packet, const UserID &clientId) {
    nlohmann::json jPack = nlohmann::json::parse(packet);
    std::cout << "-- handle Packet call -- " << std::endl;
    
    bindings::BindingType type = jPack.at("type").get<bindings::BindingType>();
    switch (type) {
    case bindings::BindingType::JoinGame:
        connectedClients_[clientId]->setUserState(bindings::State::Matchmaking);
        connectedClients_[clientId]->setGameMode(bindings::JoinGame::from_json(jPack).gameMode);
        updateThisUserWithAllhisFriends(clientId);
        matchmaking_.addPlayer(RequestJoinGame{
            Player{clientId,database_.accountManager->getUsername(clientId),},
            bindings::JoinGame::from_json(jPack)},gamesManager_);
        break;
    case bindings::BindingType::CreateGame:
        connectedClients_[clientId]->setUserState(bindings::State::Matchmaking);
        connectedClients_[clientId]->setGameMode(bindings::CreateGame::from_json(jPack).gameMode);
        updateThisUserWithAllhisFriends(clientId);
        matchmaking_.createAGame(RequestCreateGame{
            Player{clientId, database_.accountManager->getUsername(clientId)},
            bindings::CreateGame::from_json(jPack)});
        break;
    case bindings::BindingType::FriendRequest:
        socialService_.handleFriendRequest(clientId, bindings::FriendRequest::from_json(jPack),database_.accountManager);
        updateMenu(clientId);
        updateMenu(database_.accountManager->getUserId(jPack.at("data").at("targetName").get<std::string>()));
        break;
    case bindings::BindingType::Message:
        socialService_.handleMessages(clientId, bindings::Message::from_json(jPack));
        updateMenu(clientId);
        updateMenu(jPack.at("data").at("recipientId").get<UserID>());
        break;
    case bindings::BindingType::HandleFriendRequest:
        
        socialService_.handleHandleFriendRequest(clientId, bindings::HandleFriendRequest::from_json(jPack));
        updateMenu(clientId);
        updateMenu(jPack.at("data").at("user").get<UserID>());
        break;
    case bindings::BindingType::RemoveFriend:
        socialService_.handleRemoveFriend(clientId, bindings::RemoveFriend::from_json(jPack));
        updateMenu(clientId);
        updateMenu(jPack.at("data").at("playerId").get<UserID>());
        break;
    case bindings::BindingType::RemoveClient:
        removeConnection(clientId);
        break;
    default:
        
        break;
    }
}

void ClientManager::addClientInWaitingForAuth(
    std::shared_ptr<ClientLink> &&clientLink) {
    clientLink->setUserState(bindings::State::Offline);
    waitingForAuthClient.push_back(clientLink);
}

void ClientManager::handleMessage(nlohmann::json message) {
    std::lock_guard<std::mutex> lock(mutex_);
    connectedClients_[message.at("data").at("recipientId").get<int>()]
        ->sendPackage(message);
}

bool ClientManager::checkCredentials(nlohmann::json data) {
    const std::string nickname = data.at("nickname").get<std::string>();
    const std::string passwordReceive = data.at("password").get<std::string>();

    if (!database_.accountManager->checkUsernameExists(nickname)) {
        std::cout << "Invalid username" << std::endl;
        return false;
    }

    std::string storedPasswordHash = database_.accountManager->getUserPasswordHash(nickname);
    if (!bcrypt::validatePassword(passwordReceive, storedPasswordHash)) {
        std::cout << "Invalid password" << std::endl;
        return false;
    }

    if (isClientConnected(database_.accountManager->getUserId(nickname))) {
        std::cout << "User already connected" << std::endl;
        return false;
    }
    return true;
}


void ClientManager::updateMenu(UserID userID){
    if (getUserState(userID) == bindings::State::Menu ){
        connectedClients_[userID]->sendPackage(socialService_.getPendignsFriendRequests(userID).to_json());
        connectedClients_[userID]->sendPackage(socialService_.getFriendsList(userID).to_json());
        connectedClients_[userID]->sendPackage(socialService_.getConversations(userID, database_.accountManager).to_json());
    }
    
}

void ClientManager::updateGamePlayer(UserID userIds, nlohmann::json gameState) {
    if (getUserState(userIds) != bindings::State::Offline){
        if (gameState.at("type").get<bindings::BindingType>() == bindings::BindingType::GameOver){
            connectedClients_[userIds]->setUserState(bindings::State::Menu);
        } 
        connectedClients_[userIds]->sendPackage(gameState);    
    }
    
}

bool ClientManager::isClientConnected(UserID userID) {
    return connectedClients_.find(userID) != connectedClients_.end();
}
bindings::State ClientManager::getUserState(UserID userID){
    if (isClientConnected(userID)){
        return connectedClients_[userID]->getUserState();
    }else {
        return bindings::State::Offline;
    }
}

void ClientManager::updateThisUserWithAllhisFriends(UserID userId){
    bindings::User user = getUser(userId);
    for (auto id : socialService_.getFriendIdsList(userId)){
        if (isClientConnected(id)){
            connectedClients_[id]->sendPackage(user.to_json());
        }
    }
}

bindings::User ClientManager::getUser(UserID userID){

    return bindings::User{
        userID, 
        database_.accountManager->getUsername(userID), 
        getUserState(userID), 
        (getUserState(userID) != bindings::State::Offline) ? connectedClients_[userID]->getGameMode() : std::nullopt};
}

