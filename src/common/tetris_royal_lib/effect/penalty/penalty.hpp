#ifndef PENALTY_HPP
#define PENALTY_HPP

#include <memory>

class PenaltyTest;

class Penalty;
using PenaltyPtr = std::shared_ptr<Penalty>;

class Penalty {
  public:
    enum class PenaltyType {
        ReverseControls,
        InputLock,
        SpeedUp,
        Lightning,
        Blackout,
        NumPenaltyType,
    };

  protected:
    Penalty(PenaltyType penaltyType);
    Penalty(const Penalty &) = default;
    Penalty(Penalty &&) = default;
    Penalty &operator=(const Penalty &) = default;
    Penalty &operator=(Penalty &&) = default;

  public:
    virtual ~Penalty() = default;

    static PenaltyPtr makePenalty(PenaltyType bonusType);

    PenaltyType getPenaltyType() const;

  private:
    PenaltyType penaltyType_;

    friend PenaltyTest;
};

std::ostream &operator<<(std::ostream &os, Penalty::PenaltyType type);

#endif // PENALTY_HPP
