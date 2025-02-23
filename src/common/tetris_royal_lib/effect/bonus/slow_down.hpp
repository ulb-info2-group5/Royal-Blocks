#ifndef SLOW_DOWN_HPP
#define SLOW_DOWN_HPP

#include "../tick_timed_effect.hpp"
#include "bonus.hpp"

#include <cstddef>

class SlowDown final : public Bonus, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

  public:
    SlowDown();
    SlowDown(const SlowDown &) = delete;
    SlowDown(SlowDown &&) = delete;
    SlowDown &operator=(const SlowDown &) = delete;
    SlowDown &operator=(SlowDown &&) = delete;

    ~SlowDown() = default;
};

#endif // SLOW_DOWN_HPP
