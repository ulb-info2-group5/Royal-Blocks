#ifndef CLIENT_PLAYER_STATE_SELF_HPP
#define CLIENT_PLAYER_STATE_SELF_HPP

#include "../../../../common/types/types.hpp"
#include "../effects/timed_bonus.hpp"
#include "../effects/timed_penalty.hpp"
#include "abstract_player_state.hpp"

#include <nlohmann/json.hpp>

#include <deque>
#include <optional>
#include <variant>

using EffectType = std::variant<BonusType, PenaltyType>;
using EffectPrice = std::pair<EffectType, Energy>;

namespace client {

    struct PlayerStateSelf : public AbstractPlayerState {
        std::optional<UserID> penaltyTarget;

        std::optional<Energy> energy;

        std::vector<EffectPrice> effectsPrice;

        std::optional<std::deque<PenaltyType>> stashedPenalties;

        std::optional<client::TimedBonus> activeBonus;
        std::optional<client::TimedPenalty> activePenalty;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_SELF_HPP
