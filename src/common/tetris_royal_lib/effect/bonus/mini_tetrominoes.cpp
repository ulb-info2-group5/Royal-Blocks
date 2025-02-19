#include "mini_tetrominoes.hpp"

MiniTetrominoes::MiniTetrominoes() : Bonus(BonusType::MiniTetrominoes) {}

/* ----------------------------------------
 *              AbstractEffect
 * ----------------------------------------*/

AbstractTimedEffectPtr MiniTetrominoes::getAbstractTimedEffect() {
    return nullptr;
}
