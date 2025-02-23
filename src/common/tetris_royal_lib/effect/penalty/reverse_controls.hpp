#ifndef REVERSE_CONTROLS_HPP
#define REVERSE_CONTROLS_HPP

#include "../placement_timed_effect.hpp"
#include "penalty.hpp"

class ReverseControls final : public Penalty, public PlacementTimedEffect {
  private:
    // NOTE: This IS imposed in the instructions
    static constexpr size_t PIECES_NUM = 3;

  public:
    ReverseControls();
    ReverseControls(const ReverseControls &) = delete;
    ReverseControls(ReverseControls &&) = delete;
    ReverseControls &operator=(const ReverseControls &) = delete;
    ReverseControls &operator=(ReverseControls &&) = delete;

    ~ReverseControls() = default;
};

#endif // REVERSE_CONTROLS_HPP
