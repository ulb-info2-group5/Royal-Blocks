/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

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
