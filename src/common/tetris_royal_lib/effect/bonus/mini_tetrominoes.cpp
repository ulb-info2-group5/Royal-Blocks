#include "mini_tetrominoes.hpp"

MiniTetrominoes::MiniTetrominoes()
    : Bonus(BonusType::MiniTetrominoes), PlacementTimedEffect(PIECES_NUM) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr MiniTetrominoes::getAbstractTimedEffect() {
    return AbstractTimedEffect::getAbstractTimedEffect();
}
