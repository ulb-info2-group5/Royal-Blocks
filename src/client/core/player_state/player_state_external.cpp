#include "player_state_external.hpp"

nlohmann::json client::PlayerStateExternal::serialize() const {
    nlohmann::json j;
    j["playerID"] = playerID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;

    return j;
}

void client::PlayerStateExternal::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(playerID_);
    j.at("score").get_to(score_);
    j.at("isAlive").get_to(isAlive_);
}
