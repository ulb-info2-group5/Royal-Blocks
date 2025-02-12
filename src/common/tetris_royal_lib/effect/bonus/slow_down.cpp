#include "slow_down.hpp"

SlowDown::SlowDown() : Bonus(BonusType::SlowDown), TickTimedEffect(TICKS_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr SlowDown::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
