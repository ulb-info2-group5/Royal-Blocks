#ifndef TIMED_BONUS_HPP
#define TIMED_BONUS_HPP

#include "effect/bonus/bonus_type.hpp"
#include "nlohmann/json_fwd.hpp"

#include <nlohmann/json.hpp>

namespace client {

    struct TimedBonus {
        BonusType bonusType;
        double elapsedTime;

        /* ------------------------------------------------
         *          Serialization
         * ------------------------------------------------*/

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // TIMED_BONUS_HPP
