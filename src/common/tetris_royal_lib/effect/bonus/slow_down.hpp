#ifndef SLOW_DOWN_HPP
#define SLOW_DOWN_HPP

#include "../tick_timed_effect.hpp"
#include "timed_bonus.hpp"

#include <cstddef>

class SlowDown final : public TimedBonus, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

    static constexpr size_t SLOW_DOWN_FACTOR = 2;

  public:
    SlowDown();
    SlowDown(const SlowDown &) = delete;
    SlowDown(SlowDown &&) = delete;
    SlowDown &operator=(const SlowDown &) = delete;
    SlowDown &operator=(SlowDown &&) = delete;

    ~SlowDown() = default;

    bool shouldIgnoreTick();
};

#endif // SLOW_DOWN_HPP
