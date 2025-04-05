#include "tick_timed_effect.hpp"

TickTimedEffect::TickTimedEffect(size_t ticksNum)
    : ATimedEffect{}, numTicks_(ticksNum), remainingTicks_(ticksNum) {}

TickTimedEffect::TickTimedEffect(const TickTimedEffect &other)
    : TickTimedEffect{other.remainingTicks_} {}

bool TickTimedEffect::operator==(const TickTimedEffect &other) const {
    return remainingTicks_ == other.remainingTicks_;
}

void TickTimedEffect::tick() {
    if (remainingTicks_ > 0) {
        remainingTicks_--;
    }
}

bool TickTimedEffect::isFinished() const { return remainingTicks_ <= 0; }

double TickTimedEffect::getElapsedTime() const {
    return 1.0
           - static_cast<double>(remainingTicks_)
                 / static_cast<double>(numTicks_);
}

std::ostream &operator<<(std::ostream &os,
                         const TickTimedEffect &tickTimedEffect) {
    os << "placementTimedEffect(" << tickTimedEffect.remainingTicks_
       << " left)";
    return os;
}
