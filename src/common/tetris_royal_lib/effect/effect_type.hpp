#ifndef EFFECT_TYPE_HPP
#define EFFECT_TYPE_HPP

#include "bonus/bonus_type.hpp"
#include "penalty/penalty_type.hpp"

#include <variant>

using EffectType = std::variant<BonusType, PenaltyType>;

std::string toString(EffectType effectType);

#endif // EFFECT_TYPE_HPP
