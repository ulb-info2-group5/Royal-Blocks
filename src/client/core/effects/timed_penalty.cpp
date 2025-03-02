#include "timed_penalty.hpp"

nlohmann::json client::TimedPenalty::serialize() const {
    nlohmann::json j;

    j["penaltyType"] = penaltyType;
    j["elapsedTime"] = elapsedTime;

    return j;
}

void client::TimedPenalty::deserialize(const nlohmann::json &j) {
    penaltyType = j.at("penaltyType");
    elapsedTime = j.at("elapsedTime");
}
