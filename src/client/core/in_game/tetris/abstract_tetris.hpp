#ifndef CLIENT_ABSTRACT_TETRIS_HPP
#define CLIENT_ABSTRACT_TETRIS_HPP

#include "../../../../common/tetris_lib/board/board.hpp"

namespace client {

    /**
     * @brief Abtract class for Tetris.
     */
    struct AbstractTetris {
        Board board;

        virtual ~AbstractTetris() = default;

        /**
         * @brief Deserializes the Tetris.
         */
        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_TETRIS_HPP
