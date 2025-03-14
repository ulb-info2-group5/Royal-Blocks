#include "player_tetris_self.hpp"

void client::PlayerTetrisSelf::deserialize(const nlohmann::json &j) {
    playerState_.deserialize(j.at("playerState"));
    tetris_.deserialize(j.at("tetris"));
}
