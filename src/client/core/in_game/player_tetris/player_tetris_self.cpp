#include "player_tetris_self.hpp"

nlohmann::json client::PlayerTetrisSelf::serialize() const {
    nlohmann::json j;
    j["playerState"] = playerState_.serialize();
    j["tetris"] = tetris_.serialize();

    return j;
}

void client::PlayerTetrisSelf::deserialize(const nlohmann::json &j) {
    playerState_.deserialize(j.at("playerState"));
    tetris_.deserialize(j.at("tetris"));
}
