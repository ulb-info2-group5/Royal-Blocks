#include "tetris_self.hpp"
#include <optional>

nlohmann::json client::TetrisSelf::serialize() const {
    return {{"activeTetromino",
             activeTetromino_ ? activeTetromino_->serialize() : nullptr},
            {"previewTetromino",
             previewTetromino_ ? previewTetromino_->serialize() : nullptr},
            {"holdTetromino",
             holdTetromino_ ? holdTetromino_->serialize() : nullptr},
            {"board", board_.serialize()},
            {"tetrominoQueue", tetrominoQueue_.serialize()}};
}

void client::TetrisSelf::deserialize(const nlohmann::json &j) {
    if (!j.at("activeTetromino").is_null()) {
        activeTetromino_ = std::make_optional(Tetromino{});
        activeTetromino_->deserialize(j.at("activeTetromino"));
    } else {
        activeTetromino_ = std::nullopt;
    }

    if (!j.at("previewTetromino").is_null()) {
        previewTetromino_ = std::make_optional(Tetromino{});
        previewTetromino_->deserialize(j.at("previewTetromino"));
    } else {
        previewTetromino_ = std::nullopt;
    }

    board_.deserialize(j.at("board"));

    if (!j.at("holdTetromino").is_null()) {
        holdTetromino_ = std::make_optional(Tetromino{});
        holdTetromino_->deserialize(j.at("holdTetromino"));
    } else {
        holdTetromino_ = std::nullopt;
    }

    tetrominoQueue_.deserialize(j.at("tetrominoQueue"));
};
