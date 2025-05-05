#include "timed_bonus.hpp"

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp> 


void client::TimedBonus::deserialize(const nlohmann::json &j) {
    bonusType = j.at("bonusType");
    elapsedTime = j.at("elapsedTime");
}
