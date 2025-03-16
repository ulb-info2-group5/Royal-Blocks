#include "timed_penalty.hpp"

void client::TimedPenalty::deserialize(const nlohmann::json &j) {
    penaltyType = j.at("penaltyType");
    elapsedTime = j.at("elapsedTime");
}
