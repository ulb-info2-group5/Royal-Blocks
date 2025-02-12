#ifndef LIGHTNING_HPP
#define LIGHTNING_HPP

#include "../tick_timed_effect.hpp"
#include "penalty.hpp"

class Lightning final : public Penalty, public TickTimedEffect {
    // NOTE: This IS imposed in the instructions (implicitly)
    static constexpr size_t TICKS_NUM = 1;

  public:
    Lightning();
    Lightning(const Lightning &) = default;
    Lightning(Lightning &&) = delete;
    Lightning &operator=(const Lightning &) = delete;
    Lightning &operator=(Lightning &&) = delete;

    ~Lightning() = default;

    /* ----------------------------------------
     *              AbstractEffect
     * ----------------------------------------*/

    virtual AbstractTimedEffectPtr getAbstractTimedEffect();
};

#endif // LIGHTNING_HPP
