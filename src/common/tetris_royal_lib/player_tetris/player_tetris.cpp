#include "player_tetris.hpp"

nlohmann::json PlayerTetris::serializeSelf() const {
    nlohmann::json j;
    j["playerState"] = pPlayerState_->serializeSelf();

    bool emptyBoard = false;

    TimedPenaltyPtr pPenalty = pPlayerState_->getActivePenalty();
    if (pPenalty != nullptr) {
        emptyBoard = (pPenalty->getPenaltyType() == PenaltyType::Blackout);
    }

    j["tetris"] = pTetris_->serializeSelf(emptyBoard);

    return j;
}

nlohmann::json PlayerTetris::serializeExternal() const {
    nlohmann::json j;
    j["playerState"] = pPlayerState_->serializeExternal();
    j["tetris"] = pTetris_->serializeExternal();

    return j;
}
