#include "game_server.hpp"
#include "../../common/bindings/in_game/game_state_server.hpp"
#include "game_engine/game_engine.hpp"
#include "game_mode/game_mode.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <iostream>
#include <memory>
#include <ostream>
#include <ranges>
#include <vector>

constexpr size_t SECONDS_BETWEEN_TICKS = 1;

// ----------------------------------------------------------------------------
//                          PRIVATE METHODS
// ----------------------------------------------------------------------------

void GameServer::onTimerTick() {
    if (engine.gameIsFinished()) {
        context_.stop();
        return;
    }
    sendGameStates();
    std::cout << "ticking" << std::endl;
    engine.tick();

    tickTimer_.expires_at(
        tickTimer_.expiry()
        + boost::asio::chrono::seconds{SECONDS_BETWEEN_TICKS});

    tickTimer_.async_wait([this](const boost::system::error_code &ec) {
        if (!ec) {
            onTimerTick();
        }
    });
}

// ----------------------------------------------------------------------------
//                          PUBLIC METHODS
// ----------------------------------------------------------------------------

GameServer::GameServer(GameMode gameMode, std::vector<Player> &&players,
                       UpdateGamePlayer updateGamePlayer, GameID id,
                       CallBackFinishGame callBackFinishGame)
    : context_{},
      tickTimer_{context_, boost::asio::chrono::seconds{SECONDS_BETWEEN_TICKS}},
      pGameState_{std::make_shared<GameState>(
          gameMode,
          [&] {
              std::vector<PlayerState> playerStates;
              playerStates.reserve(players.size());
              std::transform(
                  players.begin(), players.end(),
                  std::back_inserter(playerStates), [](Player player) {
                      return PlayerState(player.userID, player.username);
                  });
              return playerStates;
          }())},
      engine{pGameState_}, gameId_{id}, updateGamePlayer_{updateGamePlayer},
      callBackFinishGame_{callBackFinishGame} {}

void GameServer::enqueueBinding(UserID userId, const std::string &bindingStr) {

    // Translate bindingStr to nlohmann::json
    nlohmann::json j = nlohmann::json::parse(bindingStr);

    bindings::BindingType bindingType = j.at("type");

    switch (bindingType) {

    case bindings::BindingType::BigDrop:
        boost::asio::post(context_, [this, userId]() {
            engine.bigDrop(userId);
            sendGameStates();
        });
        break;

    case bindings::BindingType::BuyBonus: {
        boost::asio::post(
            context_,
            [this, userId, buyBonus = bindings::BuyBonus::from_json(j)]() {
                engine.tryBuyEffect(userId, buyBonus.bonusType);
                sendGameStates();
            });
        break;
    }

    case bindings::BindingType::BuyPenalty: {
        boost::asio::post(
            context_,
            [this, userId, buyPenalty = bindings::BuyPenalty::from_json(j)]() {
                engine.tryBuyEffect(userId, buyPenalty.penaltyType,
                                    buyPenalty.stashForLater);
                sendGameStates();
            });
        break;
    }

    case bindings::BindingType::EmptyPenaltyStash:
        boost::asio::post(context_, [this, userId]() {
            engine.emptyPenaltyStash(userId);
            sendGameStates();
        });
        break;

    case bindings::BindingType::HoldNextTetromino:
        boost::asio::post(context_, [this, userId]() {
            engine.holdNextTetromino(userId);
            sendGameStates();
        });
        break;

    case bindings::BindingType::MoveActive: {
        boost::asio::post(
            context_,
            [this, userId, moveActive = bindings::MoveActive::from_json(j)]() {
                engine.tryMoveActive(userId, moveActive.tetrominoMove);
                sendGameStates();
            });
        break;
    }

    case bindings::BindingType::RotateActive: {
        boost::asio::post(
            context_, [this, userId,
                       rotateActive = bindings::RotateActive::from_json(j)]() {
                engine.tryRotateActive(userId, rotateActive.rotateClockwise);
                sendGameStates();
            });
        break;
    }

    case bindings::BindingType::SelectTarget: {
        boost::asio::post(
            context_, [this, userId,
                       selectTarget = bindings::SelectTarget::from_json(j)]() {
                engine.tryRotateActive(userId, selectTarget.targetId);
                sendGameStates();
            });
        break;
    }

    case bindings::BindingType::QuitGame:
        engine.quitGame(userId);
        break;

    default:
        std::cerr << "unkown binding" << std::endl;
        break;
    }
}

void GameServer::run() {
    // Setup or async engine-tick-clock
    tickTimer_.async_wait([this](const boost::system::error_code &ec) {
        if (!ec) {
            onTimerTick();
        }
    });

    context_.run();

    // End of context_.run() means the game is finished

    // notify GameManager that the game is finished
    callBackFinishGame_(gameId_);
}

void GameServer::sendGameStates() {
    for (auto player : pGameState_->getPlayerToTetris()) {
        updateGamePlayer_(player.pPlayerState->getUserID(),
                          bindings::GameStateMessage::serializeForPlayer(
                              *pGameState_, player.pPlayerState->getUserID()));
    };
}

// ==== getters ====

boost::asio::io_context &GameServer::getIoContext() { return context_; }

std::vector<UserID> GameServer::getVectorPlayersId() {
    std::vector<UserID> userIds;
    for (auto player : pGameState_->getPlayerToTetris()) {
        userIds.push_back(player.pPlayerState->getUserID());
    }
    return userIds;
}

GameMode GameServer::getGameMode() const { return pGameState_->getGameMode(); }

int GameServer::getPlayerScore(const UserID userId) const {
    return pGameState_->getPlayerState(userId)->getScore();
}
