#include "player_tetris.hpp"

#include <memory>

PlayerTetris::PlayerTetris(PlayerStatePtr &&pPlayerState)
    : pPlayerState{pPlayerState}, pTetris{std::make_shared<Tetris>()} {

    // Register the player state as an observer of the Tetris instance.
    // This allows the player state to be notified of game events such as
    // defeat.
    pTetris->addObserver(pPlayerState);
}

nlohmann::json PlayerTetris::serializeSelf() const {
    nlohmann::json j;
    j["playerState"] = pPlayerState->serializeSelf();

    bool emptyBoard = false;

    TimedPenaltyPtr pPenalty = pPlayerState->getActivePenalty();
    if (pPenalty != nullptr) {
        emptyBoard = (pPenalty->getPenaltyType() == PenaltyType::Blackout);
    }

    j["tetris"] = pTetris->serializeSelf(emptyBoard);

    return j;
}

nlohmann::json PlayerTetris::serializeExternal() const {
    nlohmann::json j;
    j["playerState"] = pPlayerState->serializeExternal();
    j["tetris"] = pTetris->serializeExternal();

    return j;
}
