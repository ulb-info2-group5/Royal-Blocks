#include "blackout.hpp"

Blackout::Blackout()
    : TimedPenalty(PenaltyType::Blackout), TickTimedEffect(TICKS_NUM) {}
