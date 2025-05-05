#ifndef CLIENT_TETRIS_SELF_HPP
#define CLIENT_TETRIS_SELF_HPP

#include "../tetromino/tetromino.hpp"
#include "../tetromino_queue/tetromino_queue.hpp"
#include "abstract_tetris.hpp"

#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace client {

    /**
     * @brief Self tetriss. "Self" means that this packet contains all the
     * information about that player, it is supposed to be sent only to the
     * player themself.
     */
    struct TetrisSelf final : public AbstractTetris {
        std::optional<Tetromino> activeTetromino;
        std::optional<Tetromino> previewTetromino;

        std::optional<Tetromino> holdTetromino;

        TetrominoQueue tetrominoQueue;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_TETRIS_SELF_HPP
