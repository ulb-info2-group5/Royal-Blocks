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

#include "abstract_game_display.hpp"

#include <deque>
#include <stdexcept>
#include <type_traits>
#include <variant>
#include <vector>

#include "../../../common/types/types.hpp"
#include "../../core/controller/controller.hpp"
#include "../../core/in_game/effects/timed_penalty.hpp"
#include "../../core/in_game/game_state/game_state.hpp"
#include "board/board.hpp"
#include "board/grid_cell.hpp"
#include "core/in_game/effects/timed_bonus.hpp"
#include "core/in_game/game_state/game_state_viewer.hpp"
#include "core/in_game/player_state/player_state_self.hpp"
#include "core/in_game/player_tetris/player_tetris_self.hpp"
#include "core/in_game/tetris/tetris_self.hpp"
#include "core/in_game/tetromino/tetromino.hpp"
#include "core/in_game/tetromino_queue/tetromino_queue.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "effect/penalty/penalty_type.hpp"
#include "vec2/vec2.hpp"

AbstractGameDisplay::AbstractGameDisplay(Controller &controller)
    : controller_{controller} {}

AbstractGameDisplay::Color
AbstractGameDisplay::colorIdToColor(unsigned colorID) {
    switch (colorID) {
    case 0:
        return AbstractGameDisplay::Color::Red;
    case 1:
        return AbstractGameDisplay::Color::Orange;
    case 2:
        return AbstractGameDisplay::Color::Yellow;
    case 3:
        return AbstractGameDisplay::Color::Green;
    case 4:
        return AbstractGameDisplay::Color::LightBlue;
    case 5:
        return AbstractGameDisplay::Color::DarkBlue;
    case 6:
        return AbstractGameDisplay::Color::Purple;
    case 8:
        return AbstractGameDisplay::Color::Pink;
    case PENALTY_BLOCKS_COLOR_ID:
        return AbstractGameDisplay::Color::Grey;

    default:
        throw std::runtime_error{"unknown colorId"};
    };
}

bool AbstractGameDisplay::isSpectating() const {
    return std::holds_alternative<client::GameStateViewer>(gameState_);
}

// pair<penalty-name, elapsedTime>
std::optional<std::pair<std::string, double>>
AbstractGameDisplay::getPenaltyInfo() const {
    if (!std::holds_alternative<client::GameState>(gameState_)) {
        return std::nullopt;
    }

    const auto &gs = std::get<client::GameState>(gameState_);

    return gs.self.playerState.activePenalty.transform(
        [](const client::TimedPenalty &penalty) {
            return std::make_pair(toString(penalty.penaltyType),
                                  penalty.elapsedTime);
        });
}

// pair<bonus-name, elapsedTime>
std::optional<std::pair<std::string, double>>
AbstractGameDisplay::getBonusInfo() const {
    if (!std::holds_alternative<client::GameState>(gameState_)) {
        return std::nullopt;
    }

    const auto &gs = std::get<client::GameState>(gameState_);

    return gs.self.playerState.activeBonus.transform(
        [](const client::TimedBonus &bonus) {
            return std::make_pair(toString(bonus.bonusType), bonus.elapsedTime);
        });
}

UserID AbstractGameDisplay::getNthOpponentUserID(size_t n) const {
    return std::visit(
        [n](const auto &gameState) {
            return gameState.externals.at(n).playerState.userID;
        },
        gameState_);
}

size_t AbstractGameDisplay::getBoardHeight() const {
    return Board::getHeight();
}

size_t AbstractGameDisplay::getBoardWidth() const { return Board::getWidth(); }

Score AbstractGameDisplay::getSelfScore() const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.playerState.score;
}

std::optional<UserID> AbstractGameDisplay::getSelectedTarget() const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.playerState.penaltyTarget;
}

Energy AbstractGameDisplay::getSelfEnergy() const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.playerState.energy.value_or(0);
}

GameMode AbstractGameDisplay::getGameMode() const {
    return std::visit([](const auto &gameState) { return gameState.gameMode; },
                      gameState_);
}

void AbstractGameDisplay::selectTarget(size_t targetIndex) {
    controller_.selectTarget(getNthOpponentUserID(targetIndex));
}

void AbstractGameDisplay::handleKeyPress(const std::string &key) {
    controller_.handleKeyPress(key);
}

void AbstractGameDisplay::quitGame() { controller_.quitGame(); }

EffectType AbstractGameDisplay::getSelectedEffectType() const {
    return controller_.getSelectedEffectType();
}

void AbstractGameDisplay::setSelectedEffectType(EffectType effectType) {
    controller_.setSelectedEffectType(effectType);
}

void AbstractGameDisplay::buyEffect(EffectType effectType) {
    controller_.buyEffect(effectType);
}

void AbstractGameDisplay::updateGameState() {
    gameState_ = controller_.getGameState();
}

std::optional<std::pair<unsigned, AbstractGameDisplay::SelfCellType>>
AbstractGameDisplay::selfCellInfoAt(int x, int y) const {
    const auto &gs = std::get<client::GameState>(gameState_);

    if (gs.self.tetris.board.get(x, y).getColorId().has_value()) {
        return std::make_pair(
            gs.self.tetris.board.get(x, y).getColorId().value(),
            AbstractGameDisplay::SelfCellType::Placed);
    }

    const std::optional<client::Tetromino> &activeTetromino =
        gs.self.tetris.activeTetromino;
    if (activeTetromino.has_value()) {
        for (auto &vec : activeTetromino->body) {
            if (activeTetromino->anchorPoint + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(activeTetromino->colorId,
                                   AbstractGameDisplay::SelfCellType::Active));
            }
        }
    }

    const std::optional<client::Tetromino> &previewTetromino =
        gs.self.tetris.previewTetromino;
    if (previewTetromino.has_value()) {
        for (auto &vec : previewTetromino->body) {
            if (previewTetromino->anchorPoint + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(previewTetromino->colorId,
                                   AbstractGameDisplay::SelfCellType::Preview));
            }
        }
    }

    return std::nullopt;
}

std::optional<unsigned>
AbstractGameDisplay::opponentsBoardGetColorIdAt(size_t opponentIdx, int x,
                                                int y) const {
    return std::visit(
        [opponentIdx, x, y](const auto &gameState) {
            return gameState.externals.at(opponentIdx)
                .tetris.board.get(x, y)
                .getColorId();
        },
        gameState_);
}

const std::string &AbstractGameDisplay::getSelfUsername() const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.playerState.username;
}

const client::Tetromino &
AbstractGameDisplay::getTetrominoQueueNth(size_t tetrominoIdx) const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.tetris.tetrominoQueue.queue.at(tetrominoIdx);
}

size_t AbstractGameDisplay::getTetrominoQueuesSize() const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.tetris.tetrominoQueue.queue.size();
}

const client::Tetromino *AbstractGameDisplay::getHoldTetromino() const {
    const auto &gs = std::get<client::GameState>(gameState_);
    return gs.self.tetris.holdTetromino
        .transform([](const auto &holdTetromino) { return &holdTetromino; })
        .value_or(nullptr);
}

const std::string &
AbstractGameDisplay::getOpponentUsername(size_t opponentIdx) const {
    return std::visit(
        [opponentIdx](const auto &gameState) -> const std::string & {
            return gameState.externals.at(opponentIdx).playerState.username;
        },
        gameState_);
}

bool AbstractGameDisplay::checkOpponentAlive(size_t opponentIdx) const {
    return std::visit(
        [opponentIdx](const auto &gameState) -> bool {
            return gameState.externals.at(opponentIdx).playerState.isAlive;
        },
        gameState_);
}

size_t AbstractGameDisplay::getNumOpponents() const {
    return std::visit(
        [](const auto &gameState) { return gameState.externals.size(); },
        gameState_);
}

const std::vector<std::pair<EffectType, Energy>> &
AbstractGameDisplay::getEffectPrices() const {
    return std::visit(
        [](const auto &gameState)
            -> const std::vector<std::pair<EffectType, Energy>> & {
            return gameState.effectsPrice;
        },
        gameState_);
}

bool AbstractGameDisplay::isWinner() const {
    return std::visit(
        [](const auto &gameState) {
            using T = std::decay_t<decltype(gameState)>;
            if constexpr (std::is_same_v<T, client::GameState>) {
                return gameState.self.playerState.isAlive;
            } else {
                return false;
            }
        },
        gameState_);
}

bool AbstractGameDisplay::gameIsFinished() const {
    return std::visit(
        [](const auto &gameState) { return gameState.isFinished; }, gameState_);
}
