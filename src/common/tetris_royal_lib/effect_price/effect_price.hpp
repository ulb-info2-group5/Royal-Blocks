#ifndef EFFECT_PRICE_HPP
#define EFFECT_PRICE_HPP

#include "../../types/types.hpp"
#include "../effect/bonus/bonus_type.hpp"
#include "../effect/penalty/penalty_type.hpp"

#include <variant>

using EffectType = std::variant<BonusType, PenaltyType>;

constexpr Energy DEFAULT_EFFECT_PRICE = 3;

Energy getEffectPrice(EffectType effectType);

#endif // EFFECT_PRICE_HPP
