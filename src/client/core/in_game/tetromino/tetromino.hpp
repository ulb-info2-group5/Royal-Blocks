#ifndef CLIENT_TETROMINO_HPP
#define CLIENT_TETROMINO_HPP

#include "../../../../common/tetris_lib/vec2/vec2.hpp"

#include <nlohmann/json_fwd.hpp>
#include <vector>

namespace client {

    /**
     * @brief Tetromino struct.
     */
    struct Tetromino {
        Vec2 anchorPoint;
        std::vector<Vec2> body;
        unsigned colorId;

        /**
         * @brief Deserializes the tetromino.
         */
        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETROMINO_HPP
