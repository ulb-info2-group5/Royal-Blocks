#include "game_server.hpp"
#include "../../common/bindings/in_game/buy_bonus.hpp"
#include "../../common/bindings/in_game/buy_penalty.hpp"
#include "../../common/bindings/in_game/game_state_server.hpp"
#include "../../common/bindings/in_game/move_active.hpp"
#include "../../common/bindings/in_game/rotate_active.hpp"
#include "game_engine/game_engine.hpp"
#include "game_mode/game_mode.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

// ----------------------------------------------------------------------------
//                          PRIVATE METHODS
// ----------------------------------------------------------------------------

void GameServer::onTimerTick() {
    if (engine.gameIsFinished()) {
        pGameState_->setIsFinished();
        sendGameStates();
        context_.stop();
        return;
    }

    engine.tick();
    sendGameStates();

    tickTimer_.expires_after(boost::asio::chrono::milliseconds{tickDelayMs_});

    if (tickDelayMs_ > MIN_TICK_DELAY_MS) {
        tickDelayMs_ -= DECREASE_TICK_DELAY_MS;
    }

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
                       GameID id, CallBackFinishGame callBackFinishGame)
    :

      tickDelayMs_{INITIAL_TICK_DELAY_MS}, context_{},
      tickTimer_{context_, boost::asio::chrono::milliseconds{tickDelayMs_}},
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
      engine{pGameState_}, gameId_{id},
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
                engine.selectTarget(userId, selectTarget.targetId);
                sendGameStates();
            });
        break;
    }

    case bindings::BindingType::QuitGame:
        engine.quitGame(userId);

        std::erase_if(pClientLinks_, [userId](auto pWeakClientLink) {
            if (std::shared_ptr<ClientLink> pClientLink =
                    pWeakClientLink.lock()) {
                        pClientLink->setUserState(bindings::State::Menu);
                        pClientLink->setGameMode(std::nullopt);
                        pClientLink->resetGame();
                return pClientLink->getUserID() == userId;
            }
            return true;
        });

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
    for (auto pWeakClient : pClientLinks_) {
        if (std::shared_ptr<ClientLink> pClientLink = pWeakClient.lock()) {
            pClientLink->sendPackage(
                bindings::GameStateMessage::serializeForPlayer(
                    *pGameState_, pClientLink->getUserID()));
        }
    }
}

void GameServer::addClientLink(std::weak_ptr<ClientLink> clientLink) {
    pClientLinks_.push_back(clientLink);
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

const std::vector<std::weak_ptr<ClientLink>> &GameServer::getClientLinks() {
    return pClientLinks_;
}
