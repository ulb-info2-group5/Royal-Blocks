#ifndef CLIENT_PLAYER_STATE_SELF_HPP
#define CLIENT_PLAYER_STATE_SELF_HPP

#include "../effects/timed_bonus.hpp"
#include "../effects/timed_penalty.hpp"
#include "effect_selector/effect_selector.hpp"

#include <nlohmann/json.hpp>

#include <cstddef>
#include <deque>
#include <optional>

using PlayerID = size_t;
using Score = size_t;
using Energy = size_t;

namespace client {

    struct PlayerStateSelf {
        PlayerID playerID_;
        Score score_;
        bool isAlive_;

        std::optional<PlayerID> penaltyTarget_;

        std::optional<Energy> energy_;

        std::optional<EffectSelector> effectSelector_;

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
