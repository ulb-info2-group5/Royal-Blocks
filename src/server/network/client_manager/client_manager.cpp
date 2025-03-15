
#include "client_manager.hpp"
#include "../../../common/bindings/ranking.hpp"

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
    std::cout << "user state: " << static_cast<int>(userState) << std::endl;
    if (getUserState() == bindings::State::Offline) {
        handleAuthentication(packet);
    } else {
        packetHandler_(packet, clientId.value());
    }
    read();
}

void ClientLink::handleErrorReading() {
    nlohmann::json removeClient = bindings::RemoveClient{}.to_json();
    if (getUserState() == bindings::State::Offline) {
        mustBeDeletedFromTheWaitingForAuthList_ = false;
        authPacketHandler_(removeClient.at("type").get<bindings::BindingType>(),
                           removeClient);
    } else {
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
      clientId(std::nullopt), packetHandler_(packetHandler),
      authPacketHandler_(authPacketHandler),
      authSuccessCallback_(authSuccessCallback) {
    start();
}

void ClientLink::start() {
    std::cout << "start client link" << std::endl;
    read();
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

bindings::State ClientLink::getUserState() { return userState; }

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
    CreateAccountStatus status = database_.accountManager->createAccount(
        data.at("nickname").get<std::string>(),
        data.at("password").get<std::string>());
    if (status == CreateAccountStatus::SUCCESS) return true;
    return false;
}

void ClientManager::disconnectClient(const UserID &userID) {
    if (!isClientConnected(userID)) {
        std::cout << "***** the client has already been disconnected  (id : ) "
                  << userID << std::endl;
    } else {

        connectedClients_[userID]->setUserState(bindings::State::Offline);
        addClientInWaitingForAuth(std::move(connectedClients_[userID]));
        removeConnection(userID);
    }
}

void ClientManager::removeConnection(const UserID &userID) {

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
        [this](std::vector<UserID> userIDs) { gameFindCallback(userIDs); }), 
    socialService_(database.friendsManager, database.messagesManager)
     {}




void ClientManager::authSuccessCall(std::shared_ptr<ClientLink> clientLink,
                                    nlohmann::json clientData) {
    addConnection(clientLink, clientData.at("nickname").get<std::string>());

    std::vector<std::pair<std::string, size_t>> ranking = database_.accountManager->getRanking();
    nlohmann::json rankingJson = bindings::Ranking{ranking}.to_json();
    clientLink->sendPackage(rankingJson);

}
void ClientManager::gameFindCallback(std::vector<PlayerID> &playersID) {
    std::cout << "== game find callback succcess ===" << std::endl;
    for (auto id : playersID) {
        std::cout << "id player : " << id << std::endl;
        connectedClients_[id]->setUserState(bindings::State::InGame);
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

    if (gamesManager_.isThisClientInGame(clientId)) {
        gamesManager_.enqueueGameBinding(clientId, packet);
        return;
    } else {
        handlePacketMenu(std::move(packet), std::move(clientId));
    }
}




void ClientManager::handlePacketMenu(const std::string &packet,
                                     const UserID &clientId) {
    nlohmann::json jPack = nlohmann::json::parse(packet);
    std::cout << "-- handle Packet call -- " << std::endl;

    bindings::BindingType type = jPack.at("type").get<bindings::BindingType>();


    switch (type) {
    case bindings::BindingType::Message:
        handleMessage(jPack);
        break;

    case bindings::BindingType::JoinGame:
        connectedClients_[clientId]->setUserState(bindings::State::Matchmaking);
        matchmaking_.addPlayer(RequestJoinGame{
            Player{clientId,database_.accountManager->getUsername(clientId),},
            bindings::JoinGame::from_json(jPack)},gamesManager_);
        break;
    case bindings::BindingType::CreateGame:
        connectedClients_[clientId]->setUserState(bindings::State::Matchmaking);
        matchmaking_.createAGame(RequestCreateGame{
            Player{clientId, database_.accountManager->getUsername(clientId)},
            bindings::CreateGame::from_json(jPack)});

        break;
    case bindings::BindingType::RemoveClient:
        removeConnection(clientId);
        break;
    case bindings::BindingType::FriendRequest:
        socialService_.handleFriendRequest(clientId, bindings::FriendRequest::from_json(jPack),database_.accountManager);
        break;
    default:

        break;
    }
   
    bindings::PendingFriendRequests pendingRequests =  socialService_.getPendignsFriendRequests(clientId, [this](UserID userID)->bindings::User { return getUser(userID) ; }); 
    connectedClients_[clientId]->sendPackage(pendingRequests.to_json());
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
    const std::string password = data.at("password").get<std::string>();

    if (!database_.accountManager->checkUsernameExists(nickname)) {
        std::cout << "Invalid username" << std::endl;
        return false;
    }

    if (!database_.accountManager->checkUserPassword(nickname, password)) {
        std::cout << "Invalid password" << std::endl;
        return false;
    }

    if (isClientConnected(database_.accountManager->getUserId(nickname))) {
        std::cout << "User already connected" << std::endl;
        return false;
    }
    return true;
}

void ClientManager::updateGamePlayer(UserID userIds, nlohmann::json gameState) {
    if (gameState.at("type").get<bindings::BindingType>() == bindings::BindingType::GameOver){
        connectedClients_[userIds]->setUserState(bindings::State::Menu);
    } 
    connectedClients_[userIds]->sendPackage(gameState);
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


bindings::User ClientManager::getUser(UserID userID){
    return bindings::User{userID, database_.accountManager->getUsername(userID), getUserState(userID)};
}