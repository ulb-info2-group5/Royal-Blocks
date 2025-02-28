#include "player_tetris.hpp"

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
