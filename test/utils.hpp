#ifndef UTILS_HPP
#define UTILS_HPP

#include "../src/tetromino/tetromino.hpp"
#include <memory>
#include <ostream>
#include <vector>

// NOTE: This doesn't really make sense but is required by cppUnit for
// testing Tetromino class
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
    os << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

// TODO: should this be in the actual Tetris class code?
void rotateTetrominoNTimes(std::unique_ptr<Tetromino> &tetromino,
                           bool rotateClockwise, int n);

#endif
