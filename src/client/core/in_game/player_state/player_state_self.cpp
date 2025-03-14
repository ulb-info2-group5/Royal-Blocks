#include "player_state_self.hpp"
#include <deque>
#include <optional>

nlohmann::json client::PlayerStateSelf::serialize() const {
    nlohmann::json j;
    j["playerID"] = userID;
    j["score"] = score;
    j["isAlive"] = isAlive;
    j["username"] = username;

    if (penaltyTarget) {
        j["penaltyTarget"] = *penaltyTarget;
    } else {
        j["penaltyTarget"] = nullptr;
    }

    if (energy) {
        j["energy"] = *energy;
    } else {
        j["energy"] = nullptr;
    }

    if (stashedPenalties) {
        nlohmann::json jstashedPenalties = nlohmann::json::array();
        for (const auto &stashedPenalty : *stashedPenalties) {
            jstashedPenalties.push_back(stashedPenalty);
        }
        j["stashedPenalties"] = jstashedPenalties;
    } else {
        j["stashedPenalties"] = nullptr;
    }

    if (activeBonus) {
        j["activeBonus"] = activeBonus->serialize();
    } else {
        j["activeBonus"] = nullptr;
    }

    if (activePenalty) {
        j["activePenalty"] = activePenalty->serialize();
    } else {
        j["activePenalty"] = nullptr;
    }

    return j;
}

void client::PlayerStateSelf::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(userID);
    j.at("score").get_to(score);
    j.at("isAlive").get_to(isAlive);
    j.at("username").get_to(username);

    if (!j.at("penaltyTarget").is_null()) {
        penaltyTarget = std::make_optional(UserID{});
        penaltyTarget = j.at("penaltyTarget").get<UserID>();
    } else {
        penaltyTarget = std::nullopt;
    }

    if (!j.at("energy").is_null()) {
        energy = std::make_optional(Energy{});
        energy = j.at("energy").get<Energy>();
    } else {
        energy = std::nullopt;
    }

    if (!j.at("stashedPenalties").is_null()) {
        stashedPenalties = std::make_optional(std::deque<PenaltyType>{});
        stashedPenalties = j.at("stashedPenalties");
    } else {
        stashedPenalties = std::nullopt;
    }

    if (!j.at("activeBonus").is_null()) {
        activeBonus = std::make_optional(client::TimedBonus{});
        activeBonus->deserialize(j.at("activeBonus"));
    } else {
        activeBonus = std::nullopt;
    }

    if (!j.at("activePenalty").is_null()) {
        activePenalty = std::make_optional(client::TimedPenalty{});
        activePenalty->deserialize(j.at("activePenalty"));
    } else {
        activePenalty = std::nullopt;
    }
}
