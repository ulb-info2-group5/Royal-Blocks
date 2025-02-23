#include "input_lock.hpp"

InputLock::InputLock()
    : TimedPenalty(PenaltyType::InputLock), PlacementTimedEffect(PIECES_NUM) {}
