#include "games_manager.hpp"
#include "../../common/bindings/in_game/game_over.hpp"

// ======== private methode ========
void GamesManager::deleteGame(GameID gameId) {
    for (auto user : gameSessions_[gameId]->getVectorPlayersId()) {
        updateGamePlayer_(user, bindings::GameOver{}.to_json());
        clientToGame_.erase(user);
    }
    if (gamethreads_[gameId].joinable()) {
        if (std::this_thread::get_id() == gamethreads_[gameId].get_id()) {
            gamethreads_[gameId].detach();
        } else {
            gamethreads_[gameId].join();
        }
    }
    gameSessions_.erase(gameId);
    gamethreads_.erase(gameId);
}

// ======== public methode ========

GamesManager::GamesManager(UpdateGamePlayer updateGamePlayer,
                           SaveScoreCallback saveScoreCallback,
                           UpdateRankingCallback updateRankingCallback)
    : updateGamePlayer_(updateGamePlayer),
      saveScoreCallback_(saveScoreCallback),
      updateRankingCallback_(updateRankingCallback) {}



std::shared_ptr<GameServer> GamesManager::startGameServeur(GameMode gameMode,
                                    std::vector<Player> players) {
    for (Player player : players) {
        clientToGame_[player.userID] = nextGameId;
    }
    
    std::shared_ptr<GameServer> gameServer = std::make_shared<GameServer>(
        gameMode, std::move(players), updateGamePlayer_, nextGameId,
        [this](GameID gameId) { callBackFinishGame(gameId); });
    gameSessions_[nextGameId] = gameServer;
    gamethreads_[nextGameId] = std::thread([gameServer]() { gameServer->run(); });
    nextGameId += 1;
    return gameServer;
}

void GamesManager::enqueueGameBinding(const std::shared_ptr<ClientLink>& clientLink,
                                      const std::string &strBindings) {
    UserID clientId = clientLink->getUserID();
    if ( std::shared_ptr<GameServer> gameServer = clientLink->getGameServer().lock()){
        boost::asio::post(gameServer->getIoContext(),[gameServer, clientId, strBindings]() {
            gameServer->enqueueBinding(clientId, strBindings);
        });
    }
    
}

void GamesManager::callBackFinishGame(GameID gameId) {
    if (gameSessions_[gameId]->getGameMode() == GameMode::Endless) {
        for (auto &user : gameSessions_[gameId]->getVectorPlayersId()) {
            int score = gameSessions_[gameId]->getPlayerScore(user);
            saveScoreCallback_(user, score);
            updateRankingCallback_();
        }
    }
    deleteGame(gameId);
}

void GamesManager::makeClientJoinGame(std::shared_ptr<ClientLink> clientLink, std::shared_ptr<GameServer> gameServer){
    gameServer->addClientLink(clientLink);
    clientLink->setUserState(bindings::State::InGame);
    clientLink->jointGame(gameServer);
    
    
}


bool GamesManager::isThisClientInGame(UserID userId) {
    bool res = clientToGame_.find(userId) != clientToGame_.end();
    std::cout << res << std::endl;
    return res;
}
