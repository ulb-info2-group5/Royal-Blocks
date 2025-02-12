#include "blackout.hpp"

Blackout::Blackout()
    : Penalty(PenaltyType::Blackout), TickTimedEffect(TICKS_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr Blackout::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
