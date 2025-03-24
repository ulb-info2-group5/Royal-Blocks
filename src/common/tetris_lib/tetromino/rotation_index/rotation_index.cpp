#include "rotation_index.hpp"
#include <cstdint>

RotationIndex::RotationIndex(int8_t rotationIdx) : index_{rotationIdx} {}

void RotationIndex::operator+=(int8_t rotationToAdd) {
    index_ += rotationToAdd;
    index_ = static_cast<int8_t>((index_ % 4 + 4) % 4);
}

RotationIndex::operator int8_t() const { return index_; }
