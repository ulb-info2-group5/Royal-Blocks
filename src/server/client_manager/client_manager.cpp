
#include "client_manager.hpp"

#include "../../common/bindings/ranking.hpp"

#include <bcrypt.h>

using json = nlohmann::json;

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
        connectedClients_.erase(userID);
    }
}


void ClientManager::removeClient(std::optional<UserID> userID){
    if (userID.has_value()){
        
        switch(getUserState(userID.value())){
            case bindings::State::InGame: 
                gamesManager_.enqueueGameBinding(connectedClients_[userID.value()], bindings::QuitGame{}.to_json().dump());
                break;
            case bindings::State::Matchmaking: 
                matchmaking_.removePlayer(userID.value(), connectedClients_[userID.value()]->getGameMode().value());
                break;
            default:
                break;
        }
        
        disconnectClient(userID.value());
    }
    removeClientsFromTheWaintingList();
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
        [this](UserID user, int score) {
            database_.accountManager->updateScore(user, score);
        },
        [this]() {
            sendUpdatedRankingToClients();
        }),
    matchmaking_(
        [this](std::vector<Player> players,GameMode gameMode ) { gameFindCallback(players, gameMode); }), 

    socialService_(database.friendsManager, database.messagesManager, 
        [this](UserID userID)->bindings::User { return getUser(userID) ; }),
    accountService_(database.accountManager)
     {}




void ClientManager::authSuccessCall(std::shared_ptr<ClientLink> clientLink,
                                    nlohmann::json clientData) {
    addConnection(clientLink, clientData.at("nickname").get<std::string>());
    std::vector<std::pair<std::string, size_t>> ranking = database_.accountManager->getRanking();
    nlohmann::json rankingJson = bindings::Ranking{ranking}.to_json();
    clientLink->sendPackage(rankingJson);
    
    

}
void ClientManager::gameFindCallback(std::vector<Player> &players,GameMode gameMode) {
    std::cout << "== game find callback succcess ===" << std::endl;
    std::shared_ptr<GameServer> gameServer = gamesManager_.startGameServeur(gameMode, players);
    for (auto player : players) {
        gamesManager_.makeClientJoinGame(connectedClients_[player.userID], gameServer);
    }
    gameServer->sendGameStates();
    
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

nlohmann::json ClientManager::authPacketHandler(nlohmann::json binding) {
    nlohmann::json response;
    
    bindings::BindingType type =  binding.at("type").get<bindings::BindingType>(); 
    switch (type) {
    case bindings::BindingType::Authentication:
        response = accountService_.authenticationAttempt(bindings::Authentication::from_json(binding),
        [this](UserID userID)->bool { return isClientConnected(userID) ; }).to_json();
        break;
    case bindings::BindingType::Registration:
        response = accountService_.attemptCreateAccount(bindings::Registration::from_json(binding)).to_json();
        break;
    default:
        break;
    }
    return response;
}

void ClientManager::handlePacket(const std::string &packet,const UserID &clientId) {
    if (connectedClients_[clientId]->getUserState() == bindings::State::InGame ) {
        gamesManager_.enqueueGameBinding(connectedClients_[clientId], packet);
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
            bindings::JoinGame::from_json(jPack)});
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
    case bindings::BindingType::ChangePassword:
        accountService_.changePassword(clientId, bindings::ChangePassword::from_json(jPack));
        break;
    case bindings::BindingType::ChangeUsername:
        connectedClients_[clientId]->sendPackage(accountService_.attemptChangeUsername(clientId, bindings::ChangeUsername::from_json(jPack), 
        [this](UserID userID){updateThisUserWithAllhisFriends(userID);}).to_json());        
        break;
    case bindings::BindingType::AbortMatchMaking:
        matchmaking_.abortMatchmaking(connectedClients_[clientId]);
        updateThisUserWithAllhisFriends(clientId);
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

