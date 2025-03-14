#include "tetromino_queue.hpp"

void client::TetrominoQueue::deserialize(const nlohmann::json &j) {
    queue_.clear();

    for (const auto &item : j) {
        Tetromino tetromino;
        tetromino.deserialize(item);
        queue_.push_back(std::move(tetromino));
    }
}
