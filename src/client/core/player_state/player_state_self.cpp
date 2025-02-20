#include "player_state_self.hpp"

nlohmann::json client::PlayerStateSelf::serialize() const {
    nlohmann::json j;
    j["playerID"] = playerID_;
    j["score"] = score_;
    j["isAlive"] = isAlive_;

    if (penaltyTarget_) {
        j["penaltyTarget"] = *penaltyTarget_;
    } else {
        j["penaltyTarget"] = nullptr;
    }

    if (energy_) {
        j["energy"] = *energy_;
    } else {
        j["energy"] = nullptr;
    }

    if (effectSelector_) {
        j["effectSelector"] = effectSelector_->serialize();
    } else {
        j["effectSelector"] = nullptr;
    }

    return j;
}

void client::PlayerStateSelf::deserialize(const nlohmann::json &j) {
    j.at("playerID").get_to(playerID_);
    j.at("score").get_to(score_);
    j.at("isAlive").get_to(isAlive_);

    if (!j.at("penaltyTarget").is_null()) {
        penaltyTarget_ = j.at("penaltyTarget").get<PlayerID>();
    } else {
        penaltyTarget_ = std::nullopt;
    }

    if (!j.at("energy").is_null()) {
        energy_ = j.at("energy").get<Energy>();
    } else {
        energy_ = std::nullopt;
    }

    if (!j.at("effectSelector").is_null()) {
        effectSelector_ = std::make_optional(EffectSelector{});
        effectSelector_->deserialize(j.at("effectSelector"));
    } else {
        effectSelector_ = std::nullopt;
    }
}
