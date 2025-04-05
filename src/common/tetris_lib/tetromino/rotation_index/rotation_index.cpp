#include "rotation_index.hpp"
#include <cstdint>

RotationIndex::RotationIndex(uint8_t rotationIdx) : index_{rotationIdx} {}

void RotationIndex::operator+=(uint8_t rotationToAdd) {
    index_ += rotationToAdd;
    index_ = static_cast<uint8_t>((index_ % NUM_ROTATIONS + NUM_ROTATIONS)
                                  % NUM_ROTATIONS);
}

RotationIndex::operator uint8_t() const { return index_; }
