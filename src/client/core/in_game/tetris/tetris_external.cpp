#include "tetris_external.hpp"

void client::TetrisExternal::deserialize(const nlohmann::json &j) {
    board.deserialize(j.at("board"));
}
