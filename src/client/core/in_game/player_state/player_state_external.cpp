#include "player_state_external.hpp"

nlohmann::json client::PlayerStateExternal::serialize() const {
    nlohmann::json j;
    j["playerID"] = userID;
    j["score"] = score;
    j["isAlive"] = isAlive;

    return j;
}

void client::PlayerStateExternal::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(userID);
    j.at("score").get_to(score);
    j.at("isAlive").get_to(isAlive);
}
