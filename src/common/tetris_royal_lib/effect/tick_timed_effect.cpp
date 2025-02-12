#include "tick_timed_effect.hpp"

TickTimedEffect::TickTimedEffect(size_t ticksNum)
    : AbstractTimedEffect(), remainingTicks_(ticksNum) {}

TickTimedEffect::TickTimedEffect(const TickTimedEffect &other)
    : TickTimedEffect{other.remainingTicks_} {}

bool TickTimedEffect::operator==(const TickTimedEffect &other) const {
    return remainingTicks_ == other.remainingTicks_;
}

void TickTimedEffect::tick() { remainingTicks_--; }

bool TickTimedEffect::isFinished() const { return remainingTicks_ <= 0; }

std::ostream &operator<<(std::ostream &os,
                         const TickTimedEffect &tickTimedEffect) {
    os << "placementTimedEffect(" << tickTimedEffect.remainingTicks_
       << " left)";
    return os;
}
