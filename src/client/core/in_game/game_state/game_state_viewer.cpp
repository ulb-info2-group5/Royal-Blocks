#include "game_state_viewer.hpp"

void client::GameStateViewer::deserialize(const nlohmann::json &j) {
    isFinished = j.at("isFinished");
    gameMode = j.at("gameMode");

    for (const auto &external : j.at("externals")) {
        PlayerTetrisExternal externalPlayer;
        externalPlayer.deserialize(external);
        externals.push_back(externalPlayer);
    }
}
