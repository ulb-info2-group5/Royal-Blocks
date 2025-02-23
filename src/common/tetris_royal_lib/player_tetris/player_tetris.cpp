#include "player_tetris.hpp"
#include "tetris/tetris.hpp"

nlohmann::json PlayerTetris::serializeSelf() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serializeSelf();

    bool emptyBoard = false;

    TimedPenaltyPtr pPenalty = playerState_.getActivePenalty();
    if (pPenalty != nullptr) {
        emptyBoard = (pPenalty->getPenaltyType() == PenaltyType::Blackout);
    }

    j["tetris"] = tetris_.serializeSelf(emptyBoard);

    return j;
}

nlohmann::json PlayerTetris::serializeExternal() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serializeExternal();
    j["tetris"] = tetris_.serializeExternal();

    return j;
}
