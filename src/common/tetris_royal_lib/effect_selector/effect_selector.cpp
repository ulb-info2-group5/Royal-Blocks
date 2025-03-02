#include "effect_selector.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "effect/penalty/penalty_type.hpp"

#include <cassert>
#include <variant>

EffectSelector::EffectSelector() : selectionIdx_{0} {
    for (size_t bonusCount = 0;
         bonusCount < static_cast<size_t>(BonusType::NumBonusType);
         bonusCount++) {
        bonuses_.at(bonusCount) = static_cast<BonusType>(bonusCount);
    }

    for (size_t penaltyCount = 0;
         penaltyCount < static_cast<size_t>(PenaltyType::NumPenaltyType);
         penaltyCount++) {
        penalties_.at(penaltyCount) = static_cast<PenaltyType>(penaltyCount);
    }

    assert(bonuses_.size() > 0 || penalties_.size() > 0);
}

void EffectSelector::select(EffectType effectType) {
    std::visit(
        [&](auto &&effectType) {
            using T = std::decay_t<decltype(effectType)>;
            if constexpr (std::is_same_v<T, BonusType>) {
                auto bonusTypeIt =
                    std::find(bonuses_.begin(), bonuses_.end(), effectType);
                selectionIdx_ = bonusTypeIt - bonuses_.begin();
            } else if constexpr (std::is_same_v<T, PenaltyType>) {
                auto penaltyTypeIt =
                    std::find(penalties_.begin(), penalties_.end(), effectType);
                selectionIdx_ =
                    bonuses_.size() + penaltyTypeIt - penalties_.begin();
            }
        },
        effectType);
}

void EffectSelector::next() {
    selectionIdx_ = (selectionIdx_ + 1) % getNumEffects();
}

void EffectSelector::prev() {
    selectionIdx_ = (selectionIdx_ + getNumEffects() - 1) % getNumEffects();
}

EffectType EffectSelector::getSelectedEffect() const {
    if (selectionIdx_ < bonuses_.size()) {
        return bonuses_.at(selectionIdx_);
    } else {
        return penalties_.at(selectionIdx_ - bonuses_.size());
    }
}

size_t EffectSelector::getSelectedIdx() const { return selectionIdx_; }

size_t EffectSelector::getNumEffects() const {
    return bonuses_.size() + penalties_.size();
}

nlohmann::json EffectSelector::serialize() const {
    return nlohmann::json{{"selectionIdx", selectionIdx_},
                          {"bonuses", bonuses_},
                          {"penalties", penalties_}};
}

void EffectSelector::deserialize(const nlohmann::json &j) {
    j.at("selectionIdx").get_to(selectionIdx_);
    j.at("bonuses").get_to(bonuses_);
    j.at("penalties").get_to(penalties_);
}
