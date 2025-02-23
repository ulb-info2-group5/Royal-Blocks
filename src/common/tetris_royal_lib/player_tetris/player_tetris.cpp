#include "player_tetris.hpp"
#include "tetris/tetris.hpp"
#include <memory>

nlohmann::json PlayerTetris::serializeSelf() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serializeSelf();

    bool emptyBoard = false;

    PenaltyPtr pPenalty =
        std::dynamic_pointer_cast<Penalty>(playerState_.getActivePenalty());
    if (pPenalty != nullptr) {
        emptyBoard =
            (pPenalty->getPenaltyType() == Penalty::PenaltyType::Blackout);
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
