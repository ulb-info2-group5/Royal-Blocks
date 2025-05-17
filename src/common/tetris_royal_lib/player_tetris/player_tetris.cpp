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
