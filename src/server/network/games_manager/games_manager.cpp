#include "games_manager.hpp"

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
}

// ======== public methode ========

GamesManager::GamesManager(UpdateGamePlayer updateGamePlayer,
            SaveScoreCallback saveScoreCallback)
        : updateGamePlayer_(updateGamePlayer),
        saveScoreCallback_(saveScoreCallback) {}


void GamesManager::startGameServeur(GameMode gameMode,
                                    std::vector<Player> players) {
    for (Player player : players) {
        std::cout << " id : " << player.userID << "name :" << player.username << std::endl;
        clientToGame_[player.userID] = nextGameId;
    }
    std::shared_ptr<GameServer> gameServer = std::make_shared<GameServer>(
        gameMode, std::move(players), updateGamePlayer_, nextGameId,
        [this](GameID gameId) { callBackFinishGame(gameId); });
    gameSessions_[nextGameId] = gameServer;
    gamethreads_[nextGameId] =
        std::thread([gameServer]() { gameServer->run(); });
    gameServer->sendGameStates();
    std::cout << " ==<< create a new game >>== gameServer id : " << nextGameId
              << std::endl;
    nextGameId += 1;
}

void GamesManager::enqueueGameBinding(int clientId,
                                      const std::string &strBindings) {
    GameID gameId = clientToGame_[clientId];
    auto gameServer = gameSessions_[gameId];
    boost::asio::post(gameServer->getIoContext(),
                      [gameServer, clientId, strBindings]() {
                          gameServer->enqueueBinding(clientId, strBindings);
                      });
    std::cout << "player id : " << clientId << " game id : " << gameId
              << " add : " << strBindings << std::endl;
}

void GamesManager::callBackFinishGame(GameID gameId) {
<<<<<<< HEAD
    if (gameSessions_[gameId]->getGameMode() == GameMode::Endless) {
        for (auto &user : gameSessions_[gameId]->getVectorPlayersId()) {
            int score = gameSessions_[gameId]->getPlayerScore(user);
            saveScoreCallback_(user, score);
        }
    }
=======
>>>>>>> 67bc8c5 (correct manage of end game with client and server (back to main menu when the game is end))
    deleteGame(gameId);

}

bool GamesManager::isThisClientInGame(UserID userId) {
    bool res = clientToGame_.find(userId) != clientToGame_.end();
    std::cout << res << std::endl;
    return res;
}