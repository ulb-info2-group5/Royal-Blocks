#ifndef INPUT_LOCK_HPP
#define INPUT_LOCK_HPP

#include "../placement_timed_effect.hpp"
#include "timed_penalty.hpp"

class InputLock final : public TimedPenalty, public PlacementTimedEffect {
  private:
    // NOTE: This IS imposed in the instructions
    static constexpr size_t PIECES_NUM = 1;

  public:
    InputLock();
    InputLock(const InputLock &) = delete;
    InputLock(InputLock &&) = delete;
    InputLock &operator=(const InputLock &) = delete;
    InputLock &operator=(InputLock &&) = delete;

    ~InputLock() = default;
};

#endif // INPUT_LOCK_HPP
