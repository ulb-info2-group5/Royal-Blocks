#include "slow_down.hpp"

SlowDown::SlowDown()
    : TimedBonus(BonusType::SlowDown), TickTimedEffect(TICKS_NUM) {}

bool SlowDown::shouldIgnoreTick() {
    return (TICKS_NUM % SLOW_DOWN_FACTOR != 0);
}
