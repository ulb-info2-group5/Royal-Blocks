#ifndef BONUS_HPP
#define BONUS_HPP

#include <memory>
#include <nlohmann/json_fwd.hpp>

#include "../abstract_timed_effect.hpp"
#include "bonus_type.hpp"

class BonusTest;

class TimedBonus;
using TimedBonusPtr = std::shared_ptr<TimedBonus>;

class TimedBonus : public virtual ATimedEffect {
  private:
    BonusType bonusType_;

  protected:
    TimedBonus(BonusType bonusType);
    TimedBonus(const TimedBonus &) = default;
    TimedBonus(TimedBonus &&) = default;
    TimedBonus &operator=(const TimedBonus &) = delete;
    TimedBonus &operator=(TimedBonus &&) = delete;

  public:
    virtual ~TimedBonus() = default;

    /**
     * @brief Creates a new Bonus instance.
     */
    static TimedBonusPtr makeBonus(BonusType bonusType);

    /**
     * @brief Returns the bonus's type.
     */
    BonusType getBonusType() const;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the bonus to json.
     */
    nlohmann::json serialize() const;

    friend BonusTest;
};

#endif // BONUS_HPP
