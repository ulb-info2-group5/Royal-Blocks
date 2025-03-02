#include "timed_bonus.hpp"

#include <nlohmann/json.hpp>

nlohmann::json client::TimedBonus::serialize() const {
    nlohmann::json j;

    j["bonusType"] = bonusType;
    j["elapsedTime"] = elapsedTime;

    return j;
}

void client::TimedBonus::deserialize(const nlohmann::json &j) {
    bonusType = j.at("bonusType");
    elapsedTime = j.at("elapsedTime");
}
