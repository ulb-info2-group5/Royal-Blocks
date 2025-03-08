#include "game_state.hpp"

nlohmann::json client::GameState::serialize() const {
    nlohmann::json j;

    j["gameMode"] = gameMode;

    j["self"] = self.serialize();

    j["externals"] = nlohmann::json::array();
    for (const auto &playerTetris : externals) {
        j["externals"].push_back(playerTetris.serialize());
    }

    return j;
}

void client::GameState::deserialize(const nlohmann::json &j) {
    self.deserialize(j.at("self"));

    gameMode = j.at("gameMode");

    for (const auto &external : j.at("externals")) {
        PlayerTetrisExternal externalPlayer;
        externalPlayer.deserialize(external);
        externals.push_back(externalPlayer);
    }
}
