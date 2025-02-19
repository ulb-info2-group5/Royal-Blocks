#ifndef MINI_TETROMINOES_HPP
#define MINI_TETROMINOES_HPP

#include "bonus.hpp"

#include <cstddef>

// TODO: Remove this class because it is useless:
// Inserting two mini tetrominoes in the player's tetromino queue can be done as
// soon as we detect that the BonusType the player picked is MiniTetrominoes.

class MiniTetrominoes final : public Bonus {
  public:
    MiniTetrominoes();

    MiniTetrominoes(const MiniTetrominoes &) = delete;
    MiniTetrominoes(MiniTetrominoes &&) = delete;
    MiniTetrominoes &operator=(const MiniTetrominoes &) = delete;
    MiniTetrominoes &operator=(MiniTetrominoes &&) = delete;

    ~MiniTetrominoes() = default;

    /* ----------------------------------------
     *              AbstractEffect
     * ----------------------------------------*/

    virtual AbstractTimedEffectPtr getAbstractTimedEffect();
};

#endif // MINI_TETROMINOES_HPP
