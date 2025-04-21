#ifndef CLIENT_ABSTRACT_PLAYER_TETRIS_HPP
#define CLIENT_ABSTRACT_PLAYER_TETRIS_HPP

#include <nlohmann/json.hpp>

namespace client {

    /**
     * @brief Abstract Player Tetris.
     */
    struct AbstractPlayerTetris {
        virtual ~AbstractPlayerTetris() = default;

        /**
         * @brief Deserializes the AbstractPlayerTetris.
         */
        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_PLAYER_TETRIS_HPP
