#ifndef PENALTY_HPP
#define PENALTY_HPP

#include "../abstract_timed_effect.hpp"
#include "penalty_type.hpp"

#include <memory>

class PenaltyTest;

class TimedPenalty;
using TimedPenaltyPtr = std::shared_ptr<TimedPenalty>;

class TimedPenalty : public virtual ATimedEffect {
  private:
    PenaltyType penaltyType_;

  protected:
    TimedPenalty(PenaltyType penaltyType);
    TimedPenalty(const TimedPenalty &) = delete;
    TimedPenalty(TimedPenalty &&) = delete;
    TimedPenalty &operator=(const TimedPenalty &) = delete;
    TimedPenalty &operator=(TimedPenalty &&) = delete;

  public:
    virtual ~TimedPenalty() = default;

    static TimedPenaltyPtr makePenalty(PenaltyType bonusType);

    /**
     * @brief Returns the penalty's type.
     */
    PenaltyType getPenaltyType() const;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the penalty to json.
     */
    nlohmann::json serialize() const;

    friend PenaltyTest;
};

#endif // PENALTY_HPP
