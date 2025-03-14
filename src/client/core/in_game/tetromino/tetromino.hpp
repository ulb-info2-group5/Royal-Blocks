#ifndef CLIENT_TETROMINO_HPP
#define CLIENT_TETROMINO_HPP

#include "vec2/vec2.hpp"

#include <vector>

namespace client {

    struct Tetromino {
        Vec2 anchorPoint;
        std::vector<Vec2> body;
        unsigned colorId;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETROMINO_HPP
