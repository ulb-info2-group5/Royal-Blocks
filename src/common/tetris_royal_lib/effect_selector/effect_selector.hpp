#ifndef EFFECT_SELECTOR_HPP
#define EFFECT_SELECTOR_HPP

#include "../effect/bonus/bonus.hpp"
#include "../effect/penalty/penalty.hpp"

#include <array>
#include <cstddef>
#include <variant>

using EffectType = std::variant<Bonus::BonusType, Penalty::PenaltyType>;

constexpr size_t NUM_BONUSES =
    static_cast<size_t>(Bonus::BonusType::NumBonusType);

constexpr size_t NUM_PENALTIES =
    static_cast<size_t>(Penalty::PenaltyType::NumPenaltyType);

constexpr size_t EFFECTS_COUNT = NUM_BONUSES + NUM_PENALTIES;

// Ensure that we cannot create an EffectSelector with 0 effects in it at
// compile time.
static_assert(EFFECTS_COUNT > 0,
              "EffectTypeArr must have at least one element");

using EffectTypeArr = std::array<EffectType, EFFECTS_COUNT>;

/**
 * @class Represents the effects (bonuses/penalties) which the player can
 * grant himself/send to other players.
 */
class EffectSelector {
  private:
    size_t selectionIdx_;

    // bonuses & penalties
    static const EffectTypeArr EFFECTS;

  public:
    EffectSelector() = default;
    EffectSelector(const EffectSelector &) = default;
    EffectSelector(EffectSelector &&) = default;
    EffectSelector &operator=(const EffectSelector &) = default;
    EffectSelector &operator=(EffectSelector &&) = default;

    ~EffectSelector() = default;

    /**
     * @brief Selects the next effect.
     */
    void next();

    /**
     * @brief Selects the previous effect.
     */
    void prev();

    /**
     * @brief Returns the selected effect.
     */
    EffectType getSelectedEffect() const;

    /**
     * @brief Returns the index of the selected effect.
     */
    size_t getSelectedIdx() const;
};

#endif // EFFECT_SELECTOR_HPP
