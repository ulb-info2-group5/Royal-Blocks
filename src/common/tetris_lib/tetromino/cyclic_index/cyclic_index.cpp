#include "cyclic_index.hpp"

CyclicIndex::CyclicIndex(size_t cycleSize, size_t startIdx)
    : cycleSize_{cycleSize}, index_{startIdx % cycleSize_} {}

CyclicIndex &CyclicIndex::operator+=(size_t rotationToAdd) {
    index_ = (index_ + rotationToAdd) % cycleSize_;
    return *this;
}

CyclicIndex &CyclicIndex::operator-=(size_t rotationToAdd) {
    index_ = (index_ + cycleSize_ - (rotationToAdd % cycleSize_)) % cycleSize_;
    return *this;
}

CyclicIndex &CyclicIndex::operator++() { return operator+=(1); }

CyclicIndex &CyclicIndex::operator--() { return operator-=(1); }

CyclicIndex::operator size_t() const { return index_; }
