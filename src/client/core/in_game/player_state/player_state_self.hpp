#ifndef CLIENT_PLAYER_STATE_SELF_HPP
#define CLIENT_PLAYER_STATE_SELF_HPP

#include "../../../../common/types/types.hpp"
#include "../effects/timed_bonus.hpp"
#include "../effects/timed_penalty.hpp"

#include <nlohmann/json.hpp>

#include <deque>
#include <optional>

using EffectType = std::variant<BonusType, PenaltyType>;
using EffectPrice = std::pair<EffectType, Energy>;

namespace client {

    struct PlayerStateSelf {
        UserID userID_;
        Score score_;
        bool isAlive_;

        std::optional<UserID> penaltyTarget_;

        std::optional<Energy> energy_;

        std::vector<EffectPrice> effectsPrice;

        std::optional<std::deque<PenaltyType>> stashedPenalties_;

        std::optional<client::TimedBonus> activeBonus_;
        std::optional<client::TimedPenalty> activePenalty_;

        /* ------------------------------------------------
         *          Serialization
         * ------------------------------------------------*/

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_PLAYER_STATE_SELF_HPP
