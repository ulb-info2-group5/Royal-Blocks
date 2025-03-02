#include "player_tetris_external.hpp"

nlohmann::json client::PlayerTetrisExternal::serialize() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serialize();
    j["tetris"] = tetris_.serialize();

    return j;
}

void client::PlayerTetrisExternal::deserialize(const nlohmann::json &j) {
    playerState_.deserialize(j.at("playerState"));
    tetris_.deserialize(j.at("tetris"));
}
