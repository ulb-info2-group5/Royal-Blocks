#include "game_state.hpp"

#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/json.hpp>
#include <utility>
#include <vector>
#include "../../../../common/types/types.hpp"
#include "core/in_game/player_tetris/player_tetris_external.hpp"
#include "core/in_game/player_tetris/player_tetris_self.hpp"

enum class BonusType;
enum class PenaltyType;

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
