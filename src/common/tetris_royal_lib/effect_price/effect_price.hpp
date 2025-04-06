#ifndef EFFECT_PRICE_HPP
#define EFFECT_PRICE_HPP

#include "../../types/types.hpp"
#include "../effect/effect_type.hpp"

using EffectPrice = std::pair<EffectType, Energy>;

constexpr Energy DEFAULT_EFFECT_PRICE = 3;

/**
 * @brief Returns the given effect's price.
 * Defaults to DEFAULT_EFFECT_PRICE if no price is specified.
 */
Energy getEffectPrice(EffectType effectType);

#endif // EFFECT_PRICE_HPP
