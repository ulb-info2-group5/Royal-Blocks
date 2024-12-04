#include "rotation_index.hpp"
#include <cstdint>

void RotationIndex::operator+=(int8_t rotationToAdd) {
    index_ += rotationToAdd;
    index_ = (index_ % 4 + 4) % 4;
}

RotationIndex::operator int8_t() const { return index_; }
