#include "tetris_self.hpp"
#include <optional>

void client::TetrisSelf::deserialize(const nlohmann::json &j) {
    if (!j.at("activeTetromino").is_null()) {
        activeTetromino = std::make_optional(Tetromino{});
        activeTetromino->deserialize(j.at("activeTetromino"));
    } else {
        activeTetromino = std::nullopt;
    }

    if (!j.at("previewTetromino").is_null()) {
        previewTetromino = std::make_optional(Tetromino{});
        previewTetromino->deserialize(j.at("previewTetromino"));
    } else {
        previewTetromino = std::nullopt;
    }

    board.deserialize(j.at("board"));

    if (!j.at("holdTetromino").is_null()) {
        holdTetromino = std::make_optional(Tetromino{});
        holdTetromino->deserialize(j.at("holdTetromino"));
    } else {
        holdTetromino = std::nullopt;
    }

    tetrominoQueue.deserialize(j.at("tetrominoQueue"));
};
