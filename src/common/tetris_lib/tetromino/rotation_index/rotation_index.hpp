#ifndef ROTATION_INDEX_HPP
#define ROTATION_INDEX_HPP

#include <cstdint>

/**
 * @class RotationIndex
 * @brief Represents a rotation index for objects that can be rotated in
 * 90-degree increments, e.g. Tetrominoes.
 */
class RotationIndex {
  private:
    uint8_t index_;
    static constexpr uint8_t NUM_ROTATIONS = 4;

  public:
    // #### Constructors ####

    RotationIndex(uint8_t rotationIdx = 0);
    RotationIndex(const RotationIndex &) = default;
    RotationIndex(RotationIndex &&) = default;

    // #### Assignment ####

    RotationIndex &operator=(const RotationIndex &) = default;
    RotationIndex &operator=(RotationIndex &&) = default;

    // #### Destructor ####

    ~RotationIndex() = default;

    // #### Operators ####

    void operator+=(uint8_t rotationToAdd);
    operator uint8_t() const;
};

#endif
