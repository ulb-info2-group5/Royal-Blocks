#include "tetris_external.hpp"

nlohmann::json client::TetrisExternal::serialize() const {
    return {{"isAlive", isAlive_}, {"board", board_.serialize()}};
}

void client::TetrisExternal::deserialize(const nlohmann::json &j) {
    j.at("isAlive").get_to(isAlive_);

    board_.deserialize(j.at("board"));
}
