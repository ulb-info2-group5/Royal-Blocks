#ifndef MINI_TETROMINOES_HPP
#define MINI_TETROMINOES_HPP

#include "../placement_timed_effect.hpp"
#include "bonus.hpp"

#include <cstddef>

class MiniTetrominoes final : public Bonus, public PlacementTimedEffect {
  private:
    // NOTE: This IS imposed in the instructions
    static constexpr size_t PIECES_NUM = 2;

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
