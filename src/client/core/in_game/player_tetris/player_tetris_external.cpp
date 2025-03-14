#include "player_tetris_external.hpp"

void client::PlayerTetrisExternal::deserialize(const nlohmann::json &j) {
    playerState_.deserialize(j.at("playerState"));
    tetris_.deserialize(j.at("tetris"));
}
