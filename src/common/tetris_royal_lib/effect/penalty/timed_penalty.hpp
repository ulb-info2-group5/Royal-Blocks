#ifndef PENALTY_HPP
#define PENALTY_HPP

#include "../abstract_timed_effect.hpp"
#include "penalty_type.hpp"

#include <memory>

class PenaltyTest;

class TimedPenalty;
using TimedPenaltyPtr = std::shared_ptr<TimedPenalty>;

class TimedPenalty : public virtual ATimedEffect {
  protected:
    TimedPenalty(PenaltyType penaltyType);
    TimedPenalty(const TimedPenalty &) = delete;
    TimedPenalty(TimedPenalty &&) = delete;
    TimedPenalty &operator=(const TimedPenalty &) = delete;
    TimedPenalty &operator=(TimedPenalty &&) = delete;

  public:
    virtual ~TimedPenalty() = default;

    static TimedPenaltyPtr makePenalty(PenaltyType bonusType);

    PenaltyType getPenaltyType() const;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const;

  private:
    PenaltyType penaltyType_;

    friend PenaltyTest;
};

#endif // PENALTY_HPP
