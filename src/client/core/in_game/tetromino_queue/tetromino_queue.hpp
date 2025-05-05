#ifndef CLIENT_TETROMINO_QUEUE_HPP
#define CLIENT_TETROMINO_QUEUE_HPP

#include "../tetromino/tetromino.hpp"

#include <deque>
#include <nlohmann/json_fwd.hpp>

namespace client {

    /**
     * @brief Tetromino-queue.
     */
    struct TetrominoQueue {
        std::deque<client::Tetromino> queue;

        /**
         * @brief Deserializes Tetromino-queue.
         */
        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETROMINO_QUEUE_HPP
