#include "input_lock.hpp"

InputLock::InputLock()
    : Penalty(PenaltyType::InputLock), PlacementTimedEffect(PIECES_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr InputLock::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
