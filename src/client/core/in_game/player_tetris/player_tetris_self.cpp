#include "player_tetris_self.hpp"

#include <map>
#include <nlohmann/json.hpp>

#include "core/in_game/player_state/player_state_self.hpp"
#include "core/in_game/tetris/tetris_self.hpp"

void client::PlayerTetrisSelf::deserialize(const nlohmann::json &j) {
    playerState.deserialize(j.at("playerState"));
    tetris.deserialize(j.at("tetris"));
}
