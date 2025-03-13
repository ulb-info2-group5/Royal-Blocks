#ifndef CLIENT_TETRIS_SELF_HPP
#define CLIENT_TETRIS_SELF_HPP

#include "../tetromino/tetromino.hpp"
#include "../tetromino_queue/tetromino_queue.hpp"
#include "board/board.hpp"

namespace client {

    struct TetrisSelf {
        std::optional<Tetromino> activeTetromino_;
        std::optional<Tetromino> previewTetromino_;

        Board board_;

        std::optional<Tetromino> holdTetromino_;

        TetrominoQueue tetrominoQueue_;

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETRIS_SELF_HPP
