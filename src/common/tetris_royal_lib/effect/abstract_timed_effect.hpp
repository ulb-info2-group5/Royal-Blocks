#ifndef ABSTRACT_TIMED_EFFECT_HPP
#define ABSTRACT_TIMED_EFFECT_HPP

#include "abstract_effect.hpp"

class AbstractTimedEffect : public virtual AbstractEffect {
  protected:
    AbstractTimedEffect() = default;
    AbstractTimedEffect(const AbstractTimedEffect &) = delete;
    AbstractTimedEffect(AbstractTimedEffect &&) = delete;
    AbstractTimedEffect &operator=(const AbstractTimedEffect &) = delete;
    AbstractTimedEffect &operator=(AbstractTimedEffect &&) = delete;

  public:
    virtual ~AbstractTimedEffect() = default;

    /**
     * @brief Notifies that a clock tick has occurred.
     */
    virtual void tick(){};

    /**
     * @brief Notifies that the active tetromino has been placed.
     */
    virtual void tetrominoPlaced(){};

    /**
     * @brief Returns true if the effect isn't active anymore; false otherwise.
     */
    virtual bool isFinished() const = 0;

    /* ----------------------------------------
     *              AbstractEffect
     * ----------------------------------------*/

    virtual AbstractTimedEffectPtr getAbstractTimedEffect() {
        return AbstractTimedEffectPtr{this};
    }
};

#endif // ABSTRACT_TIMED_EFFECT_HPP
