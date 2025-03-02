#include "reverse_controls.hpp"

ReverseControls::ReverseControls()
    : TimedPenalty(PenaltyType::ReverseControls),
      PlacementTimedEffect(PIECES_NUM) {}
