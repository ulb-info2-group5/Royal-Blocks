#include "reverse_controls.hpp"

ReverseControls::ReverseControls()
    : Penalty(PenaltyType::ReverseControls), PlacementTimedEffect(PIECES_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr ReverseControls::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
