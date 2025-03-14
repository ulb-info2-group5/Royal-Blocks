#include "player_tetris_self.hpp"

void client::PlayerTetrisSelf::deserialize(const nlohmann::json &j) {
    playerState.deserialize(j.at("playerState"));
    tetris.deserialize(j.at("tetris"));
}
