#ifndef CLIENT_TETRIS_SELF_HPP
#define CLIENT_TETRIS_SELF_HPP

#include "../tetromino/tetromino.hpp"
#include "../tetromino_queue/tetromino_queue.hpp"
#include "abstract_tetris.hpp"

namespace client {

    struct TetrisSelf : public AbstractTetris {
        std::optional<Tetromino> activeTetromino;
        std::optional<Tetromino> previewTetromino;

        std::optional<Tetromino> holdTetromino;

        TetrominoQueue tetrominoQueue;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_TETRIS_SELF_HPP
