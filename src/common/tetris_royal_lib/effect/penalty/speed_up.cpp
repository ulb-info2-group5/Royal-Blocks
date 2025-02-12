#include "speed_up.hpp"

SpeedUp::SpeedUp()
    : Penalty(PenaltyType::SpeedUp), TickTimedEffect(TICKS_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr SpeedUp::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
