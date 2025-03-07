#include "game_server.hpp"
#include "../../common/bindings/in_game/game_state_server.hpp"
#include "game_engine/game_engine.hpp"
#include "game_mode/game_mode.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <memory>
#include <ostream>
#include <vector>

constexpr size_t SECONDS_BETWEEN_TICKS = 1;

// ----------------------------------------------------------------------------
//                          PRIVATE METHODS
// ----------------------------------------------------------------------------

void GameServer::sendGameStates() {
    // for (each PlayerID) {
    // send bindings::GameStateMessage::serializeForPlayer(*pGameState_,
    // playerID);
    // }
}

void GameServer::onTimerTick() {
    if (engine.gameIsFinished()) {
        context_.stop();
        return;
    }

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

GameServer::GameServer(GameMode gameMode, std::vector<PlayerID> &&playerIds)
    : context_{},
      tickTimer_{context_, boost::asio::chrono::seconds{SECONDS_BETWEEN_TICKS}},
      pGameState_{std::make_shared<GameState>(
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

    bindings::BindingType bindingType = j.at("type");

    switch (bindingType) {

    case bindings::BindingType::BigDrop:
        boost::asio::post(context_, [this, playerId]() {
            engine.bigDrop(playerId);
            sendGameStates();
        });
        break;

    case bindings::BindingType::BuyBonus: {
        bindings::BuyBonus buyBonus = bindings::BuyBonus::from_json(j);
        boost::asio::post(context_, [this, playerId, buyBonus]() {
            engine.tryBuyEffect(playerId, buyBonus.bonusType);
            sendGameStates();
        });
        break;
    }

    case bindings::BindingType::BuyPenalty: {
        bindings::BuyPenalty buyPenalty = bindings::BuyPenalty::from_json(j);

        boost::asio::post(context_, [this, playerId, buyPenalty]() {
            engine.tryBuyEffect(playerId, buyPenalty.penaltyType,
                                buyPenalty.stashForLater);
            sendGameStates();
        });
        break;
    }

    case bindings::BindingType::EmptyPenaltyStash:
        boost::asio::post(context_, [this, playerId]() {
            engine.emptyPenaltyStash(playerId);
            sendGameStates();
        });
        break;

    case bindings::BindingType::HoldNextTetromino:
        boost::asio::post(context_, [this, playerId]() {
            engine.holdNextTetromino(playerId);
            sendGameStates();
        });
        break;

    case bindings::BindingType::MoveActive: {
        bindings::MoveActive moveActive = bindings::MoveActive::from_json(j);
        boost::asio::post(context_, [this, playerId, moveActive]() {
            engine.tryMoveActive(playerId, moveActive.tetrominoMove);
            sendGameStates();
        });
        break;
    }

    case bindings::BindingType::RotateActive: {
        bindings::RotateActive rotateActive =
            bindings::RotateActive::from_json(j);
        boost::asio::post(context_, [this, playerId, rotateActive]() {
            engine.tryRotateActive(playerId, rotateActive.rotateClockwise);
            sendGameStates();
        });
        break;
    }

    case bindings::BindingType::SelectTarget: {
        bindings::SelectTarget selectTarget =
            bindings::SelectTarget::from_json(j);
        boost::asio::post(context_, [this, playerId, selectTarget]() {
            engine.tryRotateActive(playerId, selectTarget.targetId);
            sendGameStates();
        });
        break;
    }

    case bindings::BindingType::QuitGame:
        // TODO
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
}
