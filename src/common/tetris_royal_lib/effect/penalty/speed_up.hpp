#ifndef SPEED_UP_HPP
#define SPEED_UP_HPP

#include "../tick_timed_effect.hpp"
#include "timed_penalty.hpp"

class SpeedUp final : public TimedPenalty, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

  public:
    SpeedUp();
    SpeedUp(const SpeedUp &) = delete;
    SpeedUp(SpeedUp &&) = delete;
    SpeedUp &operator=(const SpeedUp &) = delete;
    SpeedUp &operator=(SpeedUp &&) = delete;

    ~SpeedUp() = default;
};

#endif // SPEED_UP_HPP
