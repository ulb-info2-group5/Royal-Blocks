#ifndef EFFECT_PRICE_HPP
#define EFFECT_PRICE_HPP

#include "../effect/bonus/bonus_type.hpp"
#include "../effect/penalty/penalty_type.hpp"

#include <cstddef>
#include <variant>

using Energy = size_t;
using EffectType = std::variant<BonusType, PenaltyType>;

constexpr Energy DEFAULT_EFFECT_PRICE = 3;

Energy getEffectPrice(EffectType effectType);

#endif // EFFECT_PRICE_HPP
