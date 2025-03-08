#include "tetris_external.hpp"

nlohmann::json client::TetrisExternal::serialize() const {
    return {{"board", board_.serialize()}};
}

void client::TetrisExternal::deserialize(const nlohmann::json &j) {
    board_.deserialize(j.at("board"));
}
