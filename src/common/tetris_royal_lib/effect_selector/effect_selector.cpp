#include "effect_selector.hpp"
#include "effect/bonus/bonus.hpp"
#include "effect/penalty/penalty.hpp"

#include <cassert>

EffectSelector::EffectSelector() : selectionIdx_{0} {

    for (size_t bonusCount = 0;
         bonusCount < static_cast<size_t>(Bonus::BonusType::NumBonusType);
         bonusCount++) {
        bonuses_.at(bonusCount) = static_cast<Bonus::BonusType>(bonusCount);
    }

    for (size_t penaltyCount = 0; penaltyCount < static_cast<size_t>(
                                      Penalty::PenaltyType::NumPenaltyType);
         penaltyCount++) {
        penalties_.at(penaltyCount) =
            static_cast<Penalty::PenaltyType>(penaltyCount);
    }

    // TODO: add a message here if assert fails?
    assert(bonuses_.size() > 0 || penalties_.size() > 0);
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
