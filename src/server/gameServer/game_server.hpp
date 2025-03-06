#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "../../common/bindings/bindings.hpp"
#include "game_engine/game_engine.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <memory>
#include <mutex>
#include <queue>
#include <utility>
#include <variant>

using PlayerID = size_t;

using GameStatePtr = std::shared_ptr<GameState>;

// All the events that the GameServer could receive.
using EventVariant =
    std::variant<bindings::BigDrop, bindings::BuyBonus, bindings::BuyPenalty,
                 bindings::EmptyPenaltyStash, bindings::HoldNextTetromino,
                 bindings::MoveActive, bindings::RotateActive,
                 bindings::SelectTarget>;

using PlayerEvent = std::pair<PlayerID, EventVariant>;

class GameServer {
  private:
    std::queue<PlayerEvent> queue_;
    std::mutex mutex_;

    GameStatePtr pGameState_;
    GameEngine engine;

  public:
    GameServer(GameMode gameMode, std::vector<PlayerID> &&playerIds);
    GameServer(const GameServer &) = delete;
    GameServer(GameServer &&) = delete;
    GameServer &operator=(const GameServer &) = delete;
    GameServer &operator=(GameServer &&) = delete;

    void enqueueBinding(PlayerID playerId, const std::string &bindingStr);

    void handleNextEvent();
};

#endif // GAME_SERVER_HPP
