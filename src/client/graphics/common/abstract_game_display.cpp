#include "abstract_game_display.hpp"

AbstractGameDisplay::AbstractGameDisplay(Controller &controller)
    : controller_{controller} {}

bool AbstractGameDisplay::isSpectating() {
    return std::holds_alternative<client::GameStateViewer>(gameState_);
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

std::optional<std::pair<unsigned, AbstractGameDisplay::SelfCellType>>
AbstractGameDisplay::selfCellInfoAt(int x, int y) const {
    const auto &gs = std::get<client::GameState>(gameState_);

    if (gs.self.tetris.board.get(x, y).getColorId().has_value()) {
        return std::make_pair(
            gs.self.tetris.board.get(x, y).getColorId().value(),
            AbstractGameDisplay::SelfCellType::Placed);
    }

    auto &activeTetromino = gs.self.tetris.activeTetromino;
    if (activeTetromino.has_value()) {
        for (auto &vec : activeTetromino->body) {
            if (activeTetromino->anchorPoint + vec == Vec2{x, y}) {
                return std::make_optional(
                    std::make_pair(activeTetromino->colorId,
                                   AbstractGameDisplay::SelfCellType::Active));
            }
        }
    }

    auto &previewTetromino = gs.self.tetris.previewTetromino;
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

size_t AbstractGameDisplay::getNumOpponents() const {
    return std::visit(
        [](const auto &gameState) { return gameState.externals.size(); },
        gameState_);
}

bool AbstractGameDisplay::inGame() const {
    return std::visit(
        [](const auto &gameState) { return gameState.isFinished; }, gameState_);
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
