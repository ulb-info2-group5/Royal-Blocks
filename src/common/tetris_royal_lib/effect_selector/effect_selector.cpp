#include "effect_selector.hpp"

const EffectTypeArr EffectSelector::EFFECTS = []() -> EffectTypeArr {
    EffectTypeArr effectTypeArr;

    // One bonus of each type in the effects_ array
    for (size_t bonusCount = 0;
         bonusCount < static_cast<size_t>(Bonus::BonusType::NumBonusType);
         bonusCount++) {
        effectTypeArr.at(bonusCount) =
            static_cast<Bonus::BonusType>(bonusCount);
    }

    for (size_t penaltyCount = 0; penaltyCount < static_cast<size_t>(
                                      Penalty::PenaltyType::NumPenaltyType);
         penaltyCount++) {
        // must start placing penalties where the bonuses end -> NUM_BONUSES +
        // penaltyCount
        effectTypeArr.at(NUM_BONUSES + penaltyCount) =
            static_cast<Penalty::PenaltyType>(penaltyCount);
    }

    return effectTypeArr;
}();

void EffectSelector::next() {
    selectionIdx_ = (selectionIdx_ + 1) % EFFECTS.size();
}

void EffectSelector::prev() {
    selectionIdx_ = (selectionIdx_ + EFFECTS.size() - 1) % EFFECTS.size();
}

EffectType EffectSelector::getSelectedEffect() const {
    return EFFECTS.at(selectionIdx_);
}

size_t EffectSelector::getSelectedIdx() const { return selectionIdx_; }
