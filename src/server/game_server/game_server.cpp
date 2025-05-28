/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

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

#include <iostream>
#include <memory>
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

    tickTimer_.expires_after(asio::chrono::milliseconds{tickDelayMs_});

    if (tickDelayMs_ > MIN_TICK_DELAY_MS) {
        tickDelayMs_ -= DECREASE_TICK_DELAY_MS;
    }

    tickTimer_.async_wait([this](const asio::error_code &ec) {
        if (!ec) {
            onTimerTick();
        }
    });
}

void GameServer::erasmePlayer(UserID userID) {

    std::erase_if(pClientLinks_, [userID](auto pWeakClientLink) {
        if (std::shared_ptr<ClientLink> pClientLink = pWeakClientLink.lock()) {
            if (pClientLink->getUserID() == userID) {
                pClientLink->exitGame();
                return true;
            }
            return false;
        }
        return true;
    });
}

// ----------------------------------------------------------------------------
//                          PUBLIC METHODS
// ----------------------------------------------------------------------------

GameServer::GameServer(GameMode gameMode, std::vector<Player> &&players,
                       GameID id, CallBackFinishGame callBackFinishGame)
    :

      tickDelayMs_{INITIAL_TICK_DELAY_MS}, context_{},
      tickTimer_{context_, asio::chrono::milliseconds{tickDelayMs_}},
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
    try {
        nlohmann::json j = nlohmann::json::parse(bindingStr);

        bindings::BindingType bindingType = j.at(bindings::PACKET_TYPE_FIELD);

        switch (bindingType) {

        case bindings::BindingType::BigDrop:
            asio::post(context_, [this, userId]() {
                engine.bigDrop(userId);
                sendGameStates();
            });
            break;

        case bindings::BindingType::BuyBonus: {
            asio::post(
                context_,
                [this, userId, buyBonus = bindings::BuyBonus::from_json(j)]() {
                    engine.tryBuyEffect(userId, buyBonus.bonusType);
                    sendGameStates();
                });
            break;
        }

        case bindings::BindingType::BuyPenalty: {
            asio::post(
                context_, [this, userId,
                           buyPenalty = bindings::BuyPenalty::from_json(j)]() {
                    engine.tryBuyEffect(userId, buyPenalty.penaltyType,
                                        buyPenalty.stashForLater);
                    sendGameStates();
                });
            break;
        }

        case bindings::BindingType::EmptyPenaltyStash:
            asio::post(context_, [this, userId]() {
                engine.emptyPenaltyStash(userId);
                sendGameStates();
            });
            break;

        case bindings::BindingType::HoldActiveTetromino:
            asio::post(context_, [this, userId]() {
                engine.holdActiveTetromino(userId);
                sendGameStates();
            });
            break;

        case bindings::BindingType::MoveActive: {
            asio::post(
                context_, [this, userId,
                           moveActive = bindings::MoveActive::from_json(j)]() {
                    engine.tryMoveActive(userId, moveActive.tetrominoMove);
                    sendGameStates();
                });
            break;
        }

        case bindings::BindingType::RotateActive: {
            asio::post(
                context_,
                [this, userId,
                 rotateActive = bindings::RotateActive::from_json(j)]() {
                    engine.tryRotateActive(userId,
                                           rotateActive.rotateClockwise);
                    sendGameStates();
                });
            break;
        }

        case bindings::BindingType::SelectTarget: {
            asio::post(
                context_,
                [this, userId,
                 selectTarget = bindings::SelectTarget::from_json(j)]() {
                    engine.selectTarget(userId, selectTarget.targetId);
                    sendGameStates();
                });
            break;
        }

        case bindings::BindingType::QuitGame:
            erasmePlayer(userId);
            engine.quitGame(userId);
            break;

        default:
            std::cerr << "unkown binding" << std::endl;
            break;
        }
    } catch (const std::runtime_error &e) {
        std::cerr << "Received packet is not valid JSON: " << e.what()
                  << std::endl;
    }
}

void GameServer::run() {
    // Setup or async engine-tick-clock
    tickTimer_.async_wait([this](const asio::error_code &ec) {
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
    size_t i = 0;
    while (i < pClientLinks_.size()) {
        if (std::shared_ptr<ClientLink> pClientLink = pClientLinks_[i].lock()) {
            if (pClientLink->getUserState() == bindings::State::InGame) {
                pClientLink->sendPackage(
                    bindings::GameStateMessage::serializeForPlayer(
                        *pGameState_, pClientLink->getUserID()));
            } else {
                pClientLink->sendPackage(
                    bindings::GameStateMessage::serializeForViewer(
                        *pGameState_));
            }
        }
        ++i;
    }
}

void GameServer::addClientLink(std::weak_ptr<ClientLink> clientLink) {
    pClientLinks_.push_back(clientLink);
}

void GameServer::quitGameAsViewer(UserID userID) { erasmePlayer(userID); }

// ==== getters ====

std::vector<UserID> GameServer::getVectorPlayersId() {
    std::vector<UserID> userIds;
    for (auto [userId, _] : pGameState_->getUserToPlayerTetris()) {
        userIds.push_back(userId);
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
