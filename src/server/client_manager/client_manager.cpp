
#include "client_manager.hpp"

#include "../../common/bindings/in_game/quit_game.hpp"
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

void ClientManager::disconnectClient(const UserID &userID) {
    if (!isClientConnected(userID)) {
        std::cout << "the client has already been disconnected id : " << userID
                  << std::endl;
    } else {

        connectedClients_[userID]->setUserState(bindings::State::Offline);
        addClientInWaitingForAuth(std::move(connectedClients_[userID]));
        connectedClients_.erase(userID);
    }
}

void ClientManager::removeClient(std::optional<UserID> userID) {
    if (userID.has_value()) {

        switch (getUserState(userID.value())) {
        case bindings::State::InGame:
            gamesManager_.enqueueGameBinding(
                connectedClients_[userID.value()],
                bindings::QuitGame{}.to_json().dump());
            break;
        case bindings::State::Matchmaking:
            matchmaking_.removePlayer(
                userID.value(),
                connectedClients_[userID.value()]->getGameMode().value());
            break;
        default:
            break;
        }

        disconnectClient(userID.value());
    }
    removeClientsFromTheWaintingList();
}

void ClientManager::sendUpdatedRankingToClients() const {
    std::vector<std::pair<std::string, size_t>> ranking =
        accountService_.getRanking();
    nlohmann::json rankingJson = bindings::Ranking{ranking}.to_json();
    for (auto &client : connectedClients_) {
        client.second->sendPackage(rankingJson);
    }
}

// ---public ---
ClientManager::ClientManager(DataBase database)
    : accountService_(database.accountManager),
      gamesManager_(
          [this](UserID user, int score) {
              accountService_.updateScore(user, score);
          },
          [this]() { sendUpdatedRankingToClients(); }),
      matchmaking_([this](std::vector<Player> players, GameMode gameMode) {
          gameFindCallback(players, gameMode);
      }),

      socialService_(
          database.friendsManager, database.messagesManager,
          [this](UserID userID) -> bindings::User { return getUser(userID); })

{}

void ClientManager::authSuccessCall(std::shared_ptr<ClientLink> clientLink,
                                    nlohmann::json clientData) {
    addConnection(clientLink, clientData.at("nickname").get<std::string>());
    std::vector<std::pair<std::string, size_t>> ranking =
        accountService_.getRanking();
    nlohmann::json rankingJson = bindings::Ranking{ranking}.to_json();
    clientLink->sendPackage(rankingJson);
}
void ClientManager::gameFindCallback(std::vector<Player> &players,
                                     GameMode gameMode) {
    std::shared_ptr<GameServer> gameServer =
        gamesManager_.startGameServeur(gameMode, players);
    for (auto player : players) {
        gamesManager_.makeClientJoinGame(connectedClients_[player.userID],
                                         gameServer);
    }
    gameServer->sendGameStates();
}

void ClientManager::addConnection(std::shared_ptr<ClientLink> clientSession,
                                  const std::string &username) {
    std::lock_guard<std::mutex> lock(mutex_);
    const UserID id = accountService_.getUserID(username);
    clientSession->setClientId(id);
    connectedClients_[id] = clientSession;
    removeClientsFromTheWaintingList();
    connectedClients_[id]->setUserState(bindings::State::Menu);
    updateMenu(id);
}

std::optional<nlohmann::json>
ClientManager::authPacketHandler(nlohmann::json binding) {
    std::optional<nlohmann::json> response = std::nullopt;
    try {
        bindings::BindingType type = binding.at(bindings::PACKET_TYPE_FIELD)
                                         .get<bindings::BindingType>();
        switch (type) {
        case bindings::BindingType::Authentication:
            response = accountService_
                           .authenticationAttempt(
                               bindings::Authentication::from_json(binding),
                               [this](UserID userID) -> bool {
                                   return isClientConnected(userID);
                               })
                           .to_json();
            break;
        case bindings::BindingType::Registration:
            response = accountService_
                           .attemptCreateAccount(
                               bindings::Registration::from_json(binding))
                           .to_json();
            break;
        default:
            break;
        }
    } catch (nlohmann::json::exception &e) {
        std::cerr << "Received (auth) packet has wrong format : " << e.what()
                  << std::endl;
        response = std::nullopt;
    }
    return response;
}

void ClientManager::handlePacket(const std::string &packet,
                                 const UserID &userID) {
    if (connectedClients_[userID]->getUserState() == bindings::State::InGame) {
        gamesManager_.enqueueGameBinding(connectedClients_[userID], packet);
        return;
    } else {
        handlePacketMenu(packet, userID);
    }
}

void ClientManager::handlePacketMenu(const std::string &packet,
                                     const UserID &userID) {

    nlohmann::json jPack = nlohmann::json::parse(packet);
    bindings::BindingType type =
        jPack.at(bindings::PACKET_TYPE_FIELD).get<bindings::BindingType>();
    switch (type) {
    case bindings::BindingType::JoinGame:
        connectedClients_[userID]->setUserState(bindings::State::Matchmaking);
        connectedClients_[userID]->setGameMode(
            bindings::JoinGame::from_json(jPack).gameMode);
        updateThisUserWithAllhisFriends(userID);
        matchmaking_.addPlayer(
            RequestJoinGame{Player{
                                userID,
                                accountService_.getUsername(userID),
                            },
                            bindings::JoinGame::from_json(jPack)});
        break;
    case bindings::BindingType::CreateGame:
        connectedClients_[userID]->setUserState(bindings::State::Matchmaking);
        connectedClients_[userID]->setGameMode(
            bindings::CreateGame::from_json(jPack).gameMode);
        updateThisUserWithAllhisFriends(userID);
        matchmaking_.createAGame(RequestCreateGame{
            Player{userID, accountService_.getUsername(userID)},
            bindings::CreateGame::from_json(jPack)});
        break;
    case bindings::BindingType::FriendRequest:
        socialService_.handleFriendRequest(
            userID, bindings::FriendRequest::from_json(jPack),
            accountService_.getAccountManager());
        updateMenu(userID);
        updateMenu(accountService_.getUserID(
            jPack.at("data").at("targetName").get<std::string>()));
        break;
    case bindings::BindingType::Message:
        socialService_.handleMessages(userID,
                                      bindings::Message::from_json(jPack));
        updateMenu(userID);
        updateMenu(jPack.at("data").at("recipientId").get<UserID>());
        break;
    case bindings::BindingType::HandleFriendRequest:

        socialService_.handleHandleFriendRequest(
            userID, bindings::HandleFriendRequest::from_json(jPack));
        updateMenu(userID);
        updateMenu(jPack.at("data").at("user").get<UserID>());
        break;
    case bindings::BindingType::RemoveFriend:
        socialService_.handleRemoveFriend(
            userID, bindings::RemoveFriend::from_json(jPack));
        updateMenu(userID);
        updateMenu(jPack.at("data").at("playerId").get<UserID>());
        break;
    case bindings::BindingType::ChangePassword:
        accountService_.changePassword(
            userID, bindings::ChangePassword::from_json(jPack));
        break;
    case bindings::BindingType::ChangeUsername:
        connectedClients_[userID]->sendPackage(
            accountService_
                .attemptChangeUsername(
                    userID, bindings::ChangeUsername::from_json(jPack),
                    [this](UserID userID) {
                        updateThisUserWithAllhisFriends(userID);
                    })
                .to_json());
        break;
    case bindings::BindingType::AbortMatchMaking:
        matchmaking_.abortMatchmaking(connectedClients_[userID]);
        updateThisUserWithAllhisFriends(userID);
        break;

    case bindings::BindingType::ViewGame:
        gamesManager_.joinGameAsViewer(
            connectedClients_[userID],
            connectedClients_[jPack.at("data").at("targetUser").get<UserID>()]);
        break;
    case bindings::BindingType::QuitGame:
        gamesManager_.quiGameAsViewer(connectedClients_[userID]);
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

void ClientManager::updateMenu(UserID userID) {
    if (getUserState(userID) == bindings::State::Menu) {
        connectedClients_[userID]->sendPackage(
            socialService_.getPendignsFriendRequests(userID).to_json());
        connectedClients_[userID]->sendPackage(
            socialService_.getFriendsList(userID).to_json());
        connectedClients_[userID]->sendPackage(
            socialService_
                .getConversations(userID, accountService_.getAccountManager())
                .to_json());
    }
}

void ClientManager::shutdown() { gamesManager_.shutdown(); }

bool ClientManager::isClientConnected(UserID userID) {
    return connectedClients_.find(userID) != connectedClients_.end();
}
bindings::State ClientManager::getUserState(UserID userID) {
    if (isClientConnected(userID)) {
        return connectedClients_[userID]->getUserState();
    } else {
        return bindings::State::Offline;
    }
}

void ClientManager::updateThisUserWithAllhisFriends(UserID userID) {
    bindings::User user = getUser(userID);
    for (auto id : socialService_.getFriendIdsList(userID)) {
        if (isClientConnected(id)) {
            connectedClients_[id]->sendPackage(user.to_json());
        }
    }
}

bindings::User ClientManager::getUser(UserID userID) {
    return bindings::User{userID, accountService_.getUsername(userID),
                          getUserState(userID),
                          (getUserState(userID) != bindings::State::Offline)
                              ? connectedClients_[userID]->getGameMode()
                              : std::nullopt};
}
