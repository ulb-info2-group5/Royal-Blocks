#ifndef CYCLIC_INDEX_HPP
#define CYCLIC_INDEX_HPP

#include <cstddef>

/**
 * @class CyclicIndex
 * @brief Cyclic index that supports going forward and backward.
 */
class CyclicIndex {
  private:
    size_t cycleSize_;
    size_t index_;

  public:
    // #### Constructors ####

    /**
     * @brief Constructs a new CyclicIndex.
     * @param cycleSize The length of the cycle.
     * @param startIdx The index at initialization.
     */
    CyclicIndex(size_t cycleSize, size_t startIdx = 0);
    CyclicIndex(const CyclicIndex &) = default;
    CyclicIndex(CyclicIndex &&) = default;

    // #### Assignment ####

    CyclicIndex &operator=(const CyclicIndex &) = default;
    CyclicIndex &operator=(CyclicIndex &&) = default;

    // #### Destructor ####

    ~CyclicIndex() = default;

    // #### Operators ####

    CyclicIndex &operator+=(size_t rotationToAdd);
    CyclicIndex &operator-=(size_t rotationToAdd);

    CyclicIndex &operator++();
    CyclicIndex &operator--();

    operator size_t() const;
};

#endif // CYCLIC_INDEX_HPP
