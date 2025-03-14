#ifndef CLIENT_TETRIS_SELF_HPP
#define CLIENT_TETRIS_SELF_HPP

#include "../../../../common/tetris_lib/board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino_queue/tetromino_queue.hpp"

namespace client {

    struct TetrisSelf {
        std::optional<Tetromino> activeTetromino;
        std::optional<Tetromino> previewTetromino;

        Board board;

        std::optional<Tetromino> holdTetromino;

        TetrominoQueue tetrominoQueue;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETRIS_SELF_HPP
