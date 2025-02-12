#ifndef ABSTRACT_EFFECT_HPP
#define ABSTRACT_EFFECT_HPP

#include <memory>

class AbstractTimedEffect;
using AbstractTimedEffectPtr = std::shared_ptr<AbstractTimedEffect>;

class AbstractEffect {
  public:
    /**
     * @brief Returns an AbstractTimedEffectPtr to self if the cast is possible,
     * false otherwise.
     */
    virtual AbstractTimedEffectPtr getAbstractTimedEffect() { return nullptr; }
};

#endif // ABSTRACT_EFFECT_HPP
