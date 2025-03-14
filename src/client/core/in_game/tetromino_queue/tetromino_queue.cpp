#include "tetromino_queue.hpp"

void client::TetrominoQueue::deserialize(const nlohmann::json &j) {
    queue.clear();

    for (const auto &item : j) {
        Tetromino tetromino;
        tetromino.deserialize(item);
        queue.push_back(std::move(tetromino));
    }
}
