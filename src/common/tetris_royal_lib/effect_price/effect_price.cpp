#include "effect_price.hpp"

#include <unordered_map>

std::unordered_map<EffectType, Energy> effectPriceMap{};

Energy getEffectPrice(EffectType effectType) {
    Energy energyPrice = DEFAULT_EFFECT_PRICE;
    auto it = effectPriceMap.find(effectType);

    if (it != effectPriceMap.end()) {
        energyPrice = it->second;
    }

    return energyPrice;
}
