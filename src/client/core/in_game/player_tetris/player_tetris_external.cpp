#include "player_tetris_external.hpp"

#include <map>
#include <nlohmann/json.hpp>

#include "core/in_game/player_state/player_state_external.hpp"
#include "core/in_game/tetris/tetris_external.hpp"

void client::PlayerTetrisExternal::deserialize(const nlohmann::json &j) {
    playerState.deserialize(j.at("playerState"));
    tetris.deserialize(j.at("tetris"));
}
