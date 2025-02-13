#ifndef EFFECT_PRICE_HPP
#define EFFECT_PRICE_HPP

#include "../effect/bonus/bonus.hpp"
#include "../effect/penalty/penalty.hpp"

#include <cstddef>
#include <variant>

using Energy = size_t;
using EffectType = std::variant<Bonus::BonusType, Penalty::PenaltyType>;

constexpr Energy DEFAULT_EFFECT_PRICE = 3;

Energy getEffectPrice(EffectType effectType);

#endif // EFFECT_PRICE_HPP
