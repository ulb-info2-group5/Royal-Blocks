#include "effect_type.hpp"

std::string toString(EffectType effectType) {
    return std::visit([](auto &&arg) { return toString(arg); }, effectType);
}
