#include "tetris_external.hpp"

nlohmann::json client::TetrisExternal::serialize() const {
    return {{"board", board.serialize()}};
}

void client::TetrisExternal::deserialize(const nlohmann::json &j) {
    board.deserialize(j.at("board"));
}
