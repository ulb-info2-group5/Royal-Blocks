#include "tetromino_queue.hpp"

nlohmann::json client::TetrominoQueue::serialize() const {
    nlohmann::json j_queue = nlohmann::json::array();
    for (const auto &tetromino : queue_) {
        j_queue.push_back(tetromino.serialize());
    }
    return j_queue;
}

void client::TetrominoQueue::deserialize(const nlohmann::json &j) {
    queue_.clear();

    for (const auto &item : j) {
        Tetromino tetromino;
        tetromino.deserialize(item);
        queue_.push_back(std::move(tetromino));
    }
}
