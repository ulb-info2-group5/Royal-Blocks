#include "player_state_external.hpp"

nlohmann::json client::PlayerStateExternal::serialize() const {
    nlohmann::json j;
    j["playerID"] = userID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;

    return j;
}

void client::PlayerStateExternal::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(userID_);
    j.at("score").get_to(score_);
    j.at("isAlive").get_to(isAlive_);
}
