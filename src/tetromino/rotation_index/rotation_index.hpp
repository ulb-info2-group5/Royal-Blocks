#ifndef ROTATION_INDEX_HPP
#define ROTATION_INDEX_HPP

#include <cstdint>

/**
 * @class RotationIndex
 * @brief Represents a rotation index for objects that can be rotated in
 * 90-degree increments, e.g. Tetrominoes.
 */
class RotationIndex final {
  private:
    int8_t index_;

  public:
    RotationIndex(int8_t rotationIdx = 0);
    void operator+=(int8_t rotationToAdd);
    operator int8_t() const;
};

#endif
