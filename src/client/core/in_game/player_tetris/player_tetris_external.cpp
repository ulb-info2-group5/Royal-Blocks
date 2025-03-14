#include "player_tetris_external.hpp"

void client::PlayerTetrisExternal::deserialize(const nlohmann::json &j) {
    playerState.deserialize(j.at("playerState"));
    tetris.deserialize(j.at("tetris"));
}
