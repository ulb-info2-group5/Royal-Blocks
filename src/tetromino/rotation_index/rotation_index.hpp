#ifndef ROTATION_INDEX_CPP
#define ROTATION_INDEX_CPP

#include <cstdint>

class RotationIndex {
  private:
    int8_t index_ = 0;

  public:
    RotationIndex() = default;
    void operator+=(int8_t rotationToAdd);
    operator int8_t() const;
};

#endif
