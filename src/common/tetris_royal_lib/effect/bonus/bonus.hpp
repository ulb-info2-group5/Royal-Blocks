#ifndef BONUS_HPP
#define BONUS_HPP

#include "../abstract_effect.hpp"

#include <memory>

class BonusTest;

class Bonus;
using BonusPtr = std::shared_ptr<Bonus>;

class Bonus : public virtual AbstractEffect {
  public:
    enum class BonusType {
        SlowDown,
        MiniTetrominoes,
        NumBonusType,
    };

  protected:
    Bonus(BonusType bonusType);
    Bonus(const Bonus &) = default;
    Bonus(Bonus &&) = default;
    Bonus &operator=(const Bonus &) = default;
    Bonus &operator=(Bonus &&) = default;

  public:
    virtual ~Bonus() = default;

    static BonusPtr makeBonus(BonusType bonusType);

    BonusType getBonusType() const;

    /**
     * @brief Outputs the bonus to a stream.
     *
     * @param os The output stream.
     * @param bonus The Bonus to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Bonus &bonus);

  private:
    BonusType bonusType_;

    friend BonusTest;
};

std::ostream &operator<<(std::ostream &os, Bonus::BonusType type);

#endif // BONUS_HPP
