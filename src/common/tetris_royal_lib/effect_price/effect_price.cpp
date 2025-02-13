#include "effect_price.hpp"

#include <unordered_map>

std::unordered_map<EffectType, Energy> effectPriceMap{
    // Bonuses
    {Bonus::BonusType::SlowDown, DEFAULT_EFFECT_PRICE},
    {Bonus::BonusType::MiniTetrominoes, DEFAULT_EFFECT_PRICE},

    // Penalties
    {Penalty::PenaltyType::ReverseControls, DEFAULT_EFFECT_PRICE},
    {Penalty::PenaltyType::InputLock, DEFAULT_EFFECT_PRICE},
    {Penalty::PenaltyType::SpeedUp, DEFAULT_EFFECT_PRICE},
    {Penalty::PenaltyType::Lightning, DEFAULT_EFFECT_PRICE},
    {Penalty::PenaltyType::Blackout, DEFAULT_EFFECT_PRICE},
};

Energy getEffectPrice(EffectType effectType) {
    Energy energyPrice = DEFAULT_EFFECT_PRICE;
    auto it = effectPriceMap.find(effectType);

    if (it != effectPriceMap.end()) {
        energyPrice = it->second;
    }

    return energyPrice;
}
