#include "game_server.hpp"
#include "game_engine/game_engine.hpp"
#include "game_mode/game_mode.hpp"
#include "game_state/game_state.hpp"

#include <memory>
#include <mutex>
#include <vector>

GameServer::GameServer(GameMode gameMode, std::vector<PlayerID> &&playerIds)
    : pGameState_{std::make_shared<GameState>(
        gameMode,
        [&] {
            std::vector<PlayerState> playerStates;
            playerStates.reserve(playerIds.size());
            std::transform(playerIds.begin(), playerIds.end(),
                           std::back_inserter(playerStates),
                           [](PlayerID id) { return PlayerState(id); });
            return playerStates;
        }())},
      engine{pGameState_} {}

void GameServer::enqueueBinding(PlayerID playerId,
                                const std::string &bindingStr) {
    // Translate bindingStr to nlohmann::json
    nlohmann::json j = nlohmann::json::parse(bindingStr);

    // Lock the GameServer's mutex for the following reasons:
    // 1. Another thread could enqueue at the same.
    // 2. The GameServer's thread could pop to handle the next event.
    std::lock_guard<std::mutex> guard(mutex_);

    // BigDrop
    if (j.at("type") == bindings::BindingType::BigDrop) {
        queue_.push({playerId, bindings::BigDrop::from_json(j)});
    }
    // BuyBonus
    else if (j.at("type") == bindings::BindingType::BuyBonus) {
        queue_.push({playerId, bindings::BuyBonus::from_json(j)});
    }
    // BuyPenalty
    else if (j.at("type") == bindings::BindingType::BuyPenalty) {
        queue_.push({playerId, bindings::BuyPenalty::from_json(j)});
    }
    // EmptyPenaltyStash
    else if (j.at("type") == bindings::BindingType::EmptyPenaltyStash) {
        queue_.push({playerId, bindings::EmptyPenaltyStash::from_json(j)});
    }
    // HoldNextTetromino
    else if (j.at("type") == bindings::BindingType::HoldNextTetromino) {
        queue_.push({playerId, bindings::HoldNextTetromino::from_json(j)});
    }
    // MoveActive
    else if (j.at("type") == bindings::BindingType::MoveActive) {
        queue_.push({playerId, bindings::MoveActive::from_json(j)});
    }
    // RotateActive
    else if (j.at("type") == bindings::BindingType::RotateActive) {
        queue_.push({playerId, bindings::RotateActive::from_json(j)});
    }
    // SelectTarget
    else if (j.at("type") == bindings::BindingType::SelectTarget) {
        queue_.push({playerId, bindings::SelectTarget::from_json(j)});
    }
}

void GameServer::handleNextEvent() {
    std::lock_guard<std::mutex> guard(mutex_);

    if (queue_.empty()) {
        return;
    }

    // Destructure the playerID and the event from the queue's front
    auto [playerID, event] = queue_.front();
    queue_.pop();

    std::visit(
        [this, playerID](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            // TODO: handle each event
            if constexpr (std::is_same_v<T, bindings::BigDrop>) {
                engine.bigDrop(playerID);
                // handle BigDrop
            } else if constexpr (std::is_same_v<T, bindings::BuyBonus>) {
                engine.tryBuyEffect(playerID, static_cast<BonusType>(arg.bonusType));
                // handle BuyBonus
            } else if constexpr (std::is_same_v<T, bindings::BuyPenalty>) {
                engine.tryBuyEffect(playerID, static_cast<EffectType>(arg.penalyType), arg.stashForLater);
                // handle BuyPenalty
            } else if constexpr (std::is_same_v<T,
                                                bindings::EmptyPenaltyStash>) {
                // handle EmptyPenaltyStash
                engine.emptyPenaltyStash(playerID);
            } else if constexpr (std::is_same_v<T,
                                                bindings::HoldNextTetromino>) {
                engine.holdNextTetromino(playerID);
                // handle HoldNextTetromino
            } else if constexpr (std::is_same_v<T, bindings::MoveActive>) {
                engine.tryMoveActive(playerID, arg.tetrominoMove);
                // handle MoveActive
            } else if constexpr (std::is_same_v<T, bindings::RotateActive>) {
                engine.tryRotateActive(playerID, arg.rotateClockwise);
                // handle RotateActive
            }
            //} else if constexpr (std::is_same_v<T, bindings::SelectTarget>) {
                // handle SelectTarget
            //}
        },
        event);
}
