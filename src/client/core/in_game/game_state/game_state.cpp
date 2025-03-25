#include "game_state.hpp"
#include "effect/bonus/bonus_type.hpp"

void client::GameState::deserialize(const nlohmann::json &j) {
    self.deserialize(j.at("self"));

    isFinished = j.at("isFinished");
    gameMode = j.at("gameMode");

    for (const auto &external : j.at("externals")) {
        PlayerTetrisExternal externalPlayer;
        externalPlayer.deserialize(external);
        externals.push_back(externalPlayer);
    }

    for (const std::pair<BonusType, Energy> bonusTypePrice :
         j.at("bonusToPrice")) {
        effectsPrice.push_back(bonusTypePrice);
    }
    for (const std::pair<PenaltyType, Energy> penaltyTypePrice :
         j.at("penaltyToPrice")) {
        effectsPrice.push_back(penaltyTypePrice);
    }
}

std::unique_ptr<client::AbstractGameState> client::GameState::clone() const {
    return std::make_unique<GameState>(*this);
}
