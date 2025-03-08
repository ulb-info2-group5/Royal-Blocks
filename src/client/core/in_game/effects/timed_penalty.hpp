#ifndef TIMED_PENALTY_HPP
#define TIMED_PENALTY_HPP

#include "effect/penalty/penalty_type.hpp"

#include <nlohmann/json.hpp>

namespace client {

    struct TimedPenalty {
        PenaltyType penaltyType;
        double elapsedTime;

        /* ------------------------------------------------
         *          Serialization
         * ------------------------------------------------*/

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // TIMED_PENALTY_HPP
