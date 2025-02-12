#ifndef BLACKOUT_HPP
#define BLACKOUT_HPP

#include "../tick_timed_effect.hpp"
#include "penalty.hpp"

class Blackout final : public Penalty, public TickTimedEffect {
  private:
    // NOTE: This IS NOT imposed in the instructions (can change it)
    static constexpr size_t TICKS_NUM = 10;

  public:
    Blackout();
    Blackout(const Blackout &) = delete;
    Blackout(Blackout &&) = delete;
    Blackout &operator=(const Blackout &) = delete;
    Blackout &operator=(Blackout &&) = delete;

    ~Blackout() = default;

    /* ----------------------------------------
     *              AbstractEffect
     * ----------------------------------------*/

    virtual AbstractTimedEffectPtr getAbstractTimedEffect();
};

#endif // BLACKOUT_HPP
