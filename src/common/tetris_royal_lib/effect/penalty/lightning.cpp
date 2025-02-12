#include "lightning.hpp"
#include "penalty.hpp"

Lightning::Lightning()
    : Penalty(PenaltyType::Lightning), TickTimedEffect(TICKS_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr Lightning::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
