#include "tetromino_queue.hpp"

#include <nlohmann/json.hpp>
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <utility>

#include "core/in_game/tetromino/tetromino.hpp"

void client::TetrominoQueue::deserialize(const nlohmann::json &j) {
    queue.clear();

    for (const auto &item : j) {
        Tetromino tetromino;
        tetromino.deserialize(item);
        queue.push_back(std::move(tetromino));
    }
}
