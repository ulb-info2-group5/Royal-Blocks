#include "game_state_viewer.hpp"

#include "core/in_game/player_tetris/player_tetris_external.hpp"
#include <map>
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/json.hpp>
#include <vector>

void client::GameStateViewer::deserialize(const nlohmann::json &j) {
    isFinished = j.at("isFinished");
    gameMode = j.at("gameMode");

    for (const auto &external : j.at("externals")) {
        PlayerTetrisExternal externalPlayer;
        externalPlayer.deserialize(external);
        externals.push_back(externalPlayer);
    }
}
