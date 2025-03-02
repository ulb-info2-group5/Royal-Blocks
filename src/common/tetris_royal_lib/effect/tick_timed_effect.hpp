#ifndef TICK_TIMED_EFFECT_HPP
#define TICK_TIMED_EFFECT_HPP

#include "abstract_timed_effect.hpp"

#include <cstddef>
#include <ostream>

class TickTimedEffectTest;

class TickTimedEffect : public virtual AbstractTimedEffect {
  private:
    size_t numTicks_;
    // Number of ticks left before the effect expires
    // (decreases each tick)
    size_t remainingTicks_;

  protected:
    TickTimedEffect(size_t ticksNum);
    TickTimedEffect(const TickTimedEffect &);
    TickTimedEffect(TickTimedEffect &&) = delete;
    TickTimedEffect &operator=(const TickTimedEffect &) = delete;
    TickTimedEffect &operator=(TickTimedEffect &&) = delete;

  public:
    virtual ~TickTimedEffect() = default;

    bool operator==(const TickTimedEffect &other) const;

    void tick() override;

    bool isFinished() const override;

    double getElapsedTime() const override;

    /**
     * @brief Outputs the TickTimedEffect to a stream.
     *
     * @param os The output stream.
     * @param TicktTimedEffect The TickTimedEffect to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os,
                                    const TickTimedEffect &tickTimedEffect);

    friend TickTimedEffectTest;
};

#endif // TICK_TIMED_EFFECT_HPP
