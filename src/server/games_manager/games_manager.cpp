#include "games_manager.hpp"

// ======== private methode ========

void GamesManager::joinerThreadFunc() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this]() { return !finishedGames_.empty() || !running; });
        while (!finishedGames_.empty()) {
            int gameID = finishedGames_.front();
            finishedGames_.pop();
            lock.unlock();
            if (gamethreads_[gameID].joinable()) {
                gamethreads_[gameID].join();
            }
            lock.lock();
        }
    }
}

void GamesManager::notifyGameFinished(int gameID) {
    std::lock_guard<std::mutex> lock(mutex);
    finishedGames_.push(gameID);
    cv.notify_one();
}

// ======== public methode ========

GamesManager::GamesManager(SaveScoreCallback saveScoreCallback,
                           UpdateRankingCallback updateRankingCallback)
    : saveScoreCallback_(saveScoreCallback),
      updateRankingCallback_(updateRankingCallback) {
    joinerThread_ = std::thread(&GamesManager::joinerThreadFunc, this);
}

GamesManager::~GamesManager() { shutdown(); }

void GamesManager::shutdown() {
    std::cout << "shutdwon " << std::endl;
    running = false;
    cv.notify_all();
    if (joinerThread_.joinable()) {
        joinerThread_.join();
    }
}

std::shared_ptr<GameServer>
GamesManager::startGameServeur(GameMode gameMode, std::vector<Player> players) {

    std::shared_ptr<GameServer> gameServer = std::make_shared<GameServer>(
        gameMode, std::move(players), nextGameId,
        [this](GameID gameId) { callBackFinishGame(gameId); });

    gameSessions_[nextGameId] = gameServer;
    gamethreads_[nextGameId] =
        std::thread([gameServer]() { gameServer->run(); });
    nextGameId += 1;
    return gameServer;
}

void GamesManager::enqueueGameBinding(
    const std::shared_ptr<ClientLink> &clientLink,
    const std::string &strBindings) {
    UserID clientId = clientLink->getUserID();
    if (std::shared_ptr<GameServer> gameServer =
            clientLink->getGameServer().lock()) {
        gameServer->enqueueBinding(clientId, strBindings);
    }
}

void GamesManager::callBackFinishGame(GameID gameId) {
    for (auto &weakClient : gameSessions_[gameId]->getClientLinks()) {
        if (std::shared_ptr<ClientLink> clientLink = weakClient.lock()) {
            clientLink->exitGame();
        }
    }

    if (gameSessions_[gameId]->getGameMode() == GameMode::Endless) {
        for (auto &user : gameSessions_[gameId]->getVectorPlayersId()) {
            int score = gameSessions_[gameId]->getPlayerScore(user);
            saveScoreCallback_(user, score);
            updateRankingCallback_();
        }
    }
    notifyGameFinished(gameId);
}

void GamesManager::makeClientJoinGame(std::shared_ptr<ClientLink> clientLink,
                                      std::shared_ptr<GameServer> gameServer) {
    gameServer->addClientLink(clientLink);
    clientLink->setUserState(bindings::State::InGame);
    clientLink->jointGame(gameServer);
}

void GamesManager::joinGameAsViewer(
    const std::shared_ptr<ClientLink> viewerLink,
    const std::shared_ptr<ClientLink> friendLink) {
    if (friendLink->getUserState() == bindings::State::InGame) {
        viewerLink->setUserState(bindings::State::Viewer);
        if (std::shared_ptr<GameServer> gameServer =
                friendLink->getGameServer().lock()) {
            gameServer->addClientLink(viewerLink);
            viewerLink->jointGame(gameServer);
        }
    }
}

void GamesManager::quiGameAsViewer(
    const std::shared_ptr<ClientLink> &viewerLink) {
    if (viewerLink->getUserState() == bindings::State::Viewer) {
        if (std::shared_ptr<GameServer> gameServer =
                viewerLink->getGameServer().lock()) {
            gameServer->quitGameAsViewer(viewerLink->getUserID());
            viewerLink->exitGame();
        }
    }
}
