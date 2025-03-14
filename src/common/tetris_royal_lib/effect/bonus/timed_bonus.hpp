#ifndef BONUS_HPP
#define BONUS_HPP

#include "../abstract_timed_effect.hpp"
#include "bonus_type.hpp"

#include <memory>

#include <nlohmann/json.hpp>

class BonusTest;

class TimedBonus;
using TimedBonusPtr = std::shared_ptr<TimedBonus>;

class TimedBonus : public virtual AbstractTimedEffect {
  protected:
    TimedBonus(BonusType bonusType);
    TimedBonus(const TimedBonus &) = default;
    TimedBonus(TimedBonus &&) = default;
    TimedBonus &operator=(const TimedBonus &) = delete;
    TimedBonus &operator=(TimedBonus &&) = delete;

  public:
    virtual ~TimedBonus() = default;

    static TimedBonusPtr makeBonus(BonusType bonusType);

    BonusType getBonusType() const;

    /**
     * @brief Outputs the bonus to a stream.
     *
     * @param os The output stream.
     * @param bonus The Bonus to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const TimedBonus &bonus);

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const;

  private:
    BonusType bonusType_;

    friend BonusTest;
};

#endif // BONUS_HPP
