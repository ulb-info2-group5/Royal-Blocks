#include "tetromino.hpp"

#include "../coordinate/coordinate.hpp"
#include "rotation_index/rotation_index.hpp"
#include "tetromino_shapes.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

/*--------------------------------------------------
                    PROTECTED
--------------------------------------------------*/

// #### SRS Offsets Data Constants ####

const std::vector<std::vector<Coordinate>> Tetromino::O_OFFSET_DATA = {
    {{0, 0}},
    {{1, 0}},
    {{1, -1}},
    {{0, -1}},
};
const std::vector<std::vector<Coordinate>> Tetromino::I_OFFSET_DATA = {
    {{0, 0}, {0, -1}, {0, 2}, {0, -1}, {0, 2}},
    {{0, -1}, {0, 0}, {0, 0}, {-1, 0}, {2, 0}},
    {{-1, -1}, {-1, 1}, {-1, -2}, {0, 1}, {0, -2}},
    {{-1, 0}, {-1, 0}, {-1, 0}, {1, 0}, {-2, 0}},
};

const std::vector<std::vector<Coordinate>> Tetromino::ZLSJT_OFFSET_DATA = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 1}, {1, 1}, {-2, 0}, {-2, 1}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, -1}, {1, -1}, {-2, 0}, {-2, -1}},
};

// #### Constructor ####

Tetromino::Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body,
                     const std::vector<std::vector<Coordinate>> &offsetData,
                     TetrominoShape shape)
    : anchorPoint_{std::move(anchorPoint)}, body_{std::move(body)},
      offsetData_(offsetData), shape_(shape) {

    if (body_.size() != 4) {
        throw std::invalid_argument(
            "All Tetrominoes must be composed of 4 blocks");
    }

    int minRow = std::numeric_limits<int>::max();
    int maxRow = std::numeric_limits<int>::min();
    int minCol = std::numeric_limits<int>::max();
    int maxCol = std::numeric_limits<int>::min();

    for (const Coordinate &coord : body_) {
        minRow = std::min(minRow, coord.getRow());
        minCol = std::min(minCol, coord.getCol());
        maxRow = std::max(maxRow, coord.getRow());
        maxCol = std::max(maxCol, coord.getCol());
    }

    height_ = maxRow - minRow + 1;
    width_ = maxCol - minCol + 1;
}

/*--------------------------------------------------
                     PUBLIC
--------------------------------------------------*/

// #### Copy Constructor ####

Tetromino::Tetromino(const Tetromino &other) = default;

// #### Destructor ####

Tetromino::~Tetromino() = default;

// #### Factory ####

std::unique_ptr<Tetromino> Tetromino::makeTetromino(TetrominoShape shape,
                                                    Coordinate &&anchorPoint) {
    if (shape == TetrominoShape::NumTetrominoShape) {
        throw std::runtime_error(
            "shape must be different from NumTetrominoShape");
    }

    std::unique_ptr<Tetromino> ret;

    switch (shape) {
    case (TetrominoShape::Z):
        ret = std::make_unique<TetrominoZ>(std::move(anchorPoint));
        break;
    case (TetrominoShape::L):
        ret = std::make_unique<TetrominoL>(std::move(anchorPoint));
        break;
    case (TetrominoShape::O):
        ret = std::make_unique<TetrominoO>(std::move(anchorPoint));
        break;
    case (TetrominoShape::S):
        ret = std::make_unique<TetrominoS>(std::move(anchorPoint));
        break;
    case (TetrominoShape::I):
        ret = std::make_unique<TetrominoI>(std::move(anchorPoint));
        break;
    case (TetrominoShape::J):
        ret = std::make_unique<TetrominoJ>(std::move(anchorPoint));
        break;
    case (TetrominoShape::T):
        ret = std::make_unique<TetrominoT>(std::move(anchorPoint));
        break;
    default:
        break;
    }

    return ret;
}

// #### Getters ####

size_t Tetromino::getWidth() const noexcept { return width_; }

size_t Tetromino::getHeight() const noexcept { return height_; }

TetrominoShape Tetromino::getShape() const noexcept { return shape_; }

const Coordinate &Tetromino::getAnchorPoint() const noexcept {
    return anchorPoint_;
}

const std::vector<Coordinate> &Tetromino::getBody() const noexcept {
    return body_;
}

unsigned Tetromino::getColorId() const noexcept {
    return static_cast<unsigned>(getShape());
}

const RotationIndex &Tetromino::getRotationIndex() const noexcept {
    return rotationIdx_;
}

const RotationIndex &Tetromino::getPrevRotationIndex() const noexcept {
    return prevRotationIdx_;
}

uint8_t Tetromino::getNumOfTests() const noexcept {
    return static_cast<uint8_t>(offsetData_[0].size());
}

std::unique_ptr<Tetromino>
Tetromino::getNthOffset(uint8_t offsetIndex) const noexcept {
    std::unique_ptr<Tetromino> copy = std::make_unique<Tetromino>(*this);

    Coordinate offsetVal1 = offsetData_[prevRotationIdx_][offsetIndex - 1];
    Coordinate offsetVal2 = offsetData_[rotationIdx_][offsetIndex - 1];

    // Compute offset with offset data
    Coordinate offset = (offsetVal1 - offsetVal2);

    // Apply offset
    copy->anchorPoint_ += offset;

    return copy;
}

// #### Setters ####

void Tetromino::setAnchorPoint(const Coordinate &anchorPoint) {
    anchorPoint_ = anchorPoint;
}

// #### Tetromino Actions ####

void Tetromino::move(Direction direction, bool reverse) {
    switch (direction) {
    case Direction::Down:
        anchorPoint_.moveRow(reverse ? -1 : +1);
        break;
    case Direction::Left:
        anchorPoint_.moveCol(reverse ? +1 : -1);
        break;
    case Direction::Right:
        anchorPoint_.moveCol(reverse ? -1 : +1);
        break;
    }
}

void Tetromino::rotate(bool rotateClockwise) {
    prevRotationIdx_ = rotationIdx_;
    rotationIdx_ += (rotateClockwise) ? 1 : -1;

    Coordinate center{0, 0}; // Convention : rotation center is always (0,0)

    for (Coordinate &coord : body_) {
        coord.rotateAround(center, rotateClockwise);
    }

    std::swap(height_, width_);
}

// #### Comparisons Operators ####

bool Tetromino::operator==(const Tetromino &other) const {
    return (
        std::equal(getBody().begin(), getBody().end(), other.getBody().begin())
        and getAnchorPoint() == other.getAnchorPoint()
        and getRotationIndex() == other.getRotationIndex()
        and getPrevRotationIndex() == other.getPrevRotationIndex()
        and getWidth() == other.getWidth() and getHeight() == other.getHeight()
        and getShape() == other.getShape());
}

bool Tetromino::operator!=(const Tetromino &other) const {
    return !(operator==(other));
}

// #### Output Stream ####

std::ostream &operator<<(std::ostream &os, const Tetromino &tetromino) {
    os << "anchor: " << tetromino.getAnchorPoint() << " body: {";
    for (const auto &coord : tetromino.getBody()) {
        std::cout << coord << " ";
    }
    std::cout << "}";
    return os;
}
