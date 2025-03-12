#include "effect_price.hpp"

#include <unordered_map>

std::unordered_map<EffectType, Energy> effectPriceMap{
    // Bonuses
    {BonusType::SlowDown, DEFAULT_EFFECT_PRICE},
    {BonusType::MiniTetrominoes, DEFAULT_EFFECT_PRICE},

    // Penalties
    {PenaltyType::ReverseControls, DEFAULT_EFFECT_PRICE},
    {PenaltyType::InputLock, DEFAULT_EFFECT_PRICE},
    {PenaltyType::SpeedUp, DEFAULT_EFFECT_PRICE},
    {PenaltyType::Lightning, DEFAULT_EFFECT_PRICE},
    {PenaltyType::Blackout, DEFAULT_EFFECT_PRICE},
};

Energy getEffectPrice(EffectType effectType) {
    Energy energyPrice = DEFAULT_EFFECT_PRICE;
    auto it = effectPriceMap.find(effectType);

    if (it != effectPriceMap.end()) {
        energyPrice = it->second;
    }

    return energyPrice;
}
