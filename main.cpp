#include "game_engine/game_engine.hpp"
#include "src/client/core/game_state/game_state.hpp"
// #include "effect/penalty/penalty_type.hpp"
// #include "game_engine/game_engine.hpp"
#include "game_mode/game_mode.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"

#include <vector>

int main() {

    std::vector<PlayerState> playerStates = {PlayerState{1}, PlayerState{2},
                                             PlayerState{3}};

    // GameState gameState{GameMode::RoyalCompetition, std::move(playerStates)};

    std::shared_ptr<GameState> pGameState = std::make_shared<GameState>(
        GameMode::RoyalCompetition, std::move(playerStates));

    GameEngine engine{pGameState};

    // gameState.getPlayerState(1)->stashPenalty(PenaltyType::ReverseControls);
    // gameState.getPlayerState(1)->stashPenalty(PenaltyType::InputLock);

    // client::GameState clientOneGS;
    // gameState.serializeFor(1);
    // clientOneGS.deserialize(gameState.serializeFor(1));

    // std::cout << clientOneGS.serialize() << std::endl;

    // std::cout << clientOneGS.serialize() << std::endl;

    // GameStatePtr pGameState2 = pGameState;
    // std::cout << pGameState2->getPlayerState(1)->getPlayerID() <<
    // std::endl;

    // engine.selectNextAliveTarget(1);

    // std::cout << *pGameState->getPlayerState(1)->getPenaltyTarget()
    //           << std::endl;

    return 0;
}
