#include "player_state_external.hpp"

void client::PlayerStateExternal::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(userID);
    j.at("score").get_to(score);
    j.at("isAlive").get_to(isAlive);
    j.at("username").get_to(username);
}
