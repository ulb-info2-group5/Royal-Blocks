#ifndef CLIENT_TETROMINO_QUEUE_HPP
#define CLIENT_TETROMINO_QUEUE_HPP

#include "../tetromino/tetromino.hpp"

#include <deque>

namespace client {

    struct TetrominoQueue {
        std::deque<client::Tetromino> queue;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETROMINO_QUEUE_HPP
