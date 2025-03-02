#ifndef EFFECT_SELECTOR_HPP
#define EFFECT_SELECTOR_HPP

#include "../effect/bonus/bonus_type.hpp"
#include "../effect/penalty/penalty_type.hpp"

#include <nlohmann/json.hpp>

#include <cstddef>
#include <variant>

using EffectType = std::variant<BonusType, PenaltyType>;

/**
 * @class Represents the effects (bonuses/penalties) which the player can
 * grant himself/send to other players.
 */
class EffectSelector {
  private:
    size_t selectionIdx_;

    // bonuses & penalties
    std::array<BonusType, static_cast<size_t>(BonusType::NumBonusType)>
        bonuses_;
    std::array<PenaltyType, static_cast<size_t>(PenaltyType::NumPenaltyType)>
        penalties_;

  public:
    EffectSelector();
    EffectSelector(const EffectSelector &) = default;
    EffectSelector(EffectSelector &&) = default;
    EffectSelector &operator=(const EffectSelector &) = default;
    EffectSelector &operator=(EffectSelector &&) = default;

    ~EffectSelector() = default;

    /**
     * @brief Selects the given effect.
     */
    void select(EffectType effectType);

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

    size_t getNumEffects() const;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const;

    void deserialize(const nlohmann::json &j);
};

#endif // EFFECT_SELECTOR_HPP
