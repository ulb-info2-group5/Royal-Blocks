#include "tetromino.hpp"

#include "../vec2/vec2.hpp"
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

const std::vector<std::vector<Vec2>> Tetromino::O_OFFSET_DATA = {
    {{0, 0}},
    {{1, 0}},
    {{1, -1}},
    {{0, -1}},
};
const std::vector<std::vector<Vec2>> Tetromino::I_OFFSET_DATA = {
    {{0, 0}, {0, -1}, {0, 2}, {0, -1}, {0, 2}},
    {{0, -1}, {0, 0}, {0, 0}, {-1, 0}, {2, 0}},
    {{-1, -1}, {-1, 1}, {-1, -2}, {0, 1}, {0, -2}},
    {{-1, 0}, {-1, 0}, {-1, 0}, {1, 0}, {-2, 0}},
};

const std::vector<std::vector<Vec2>> Tetromino::ZLSJT_OFFSET_DATA = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, 1}, {1, 1}, {-2, 0}, {-2, 1}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {0, -1}, {1, -1}, {-2, 0}, {-2, -1}},
};

// #### Constructor ####

Tetromino::Tetromino(Vec2 &&anchorPoint, std::vector<Vec2> &&body,
                     const std::vector<std::vector<Vec2>> &offsetData,
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

    for (const Vec2 &coord : body_) {
        minRow = std::min(minRow, coord.getY());
        minCol = std::min(minCol, coord.getX());
        maxRow = std::max(maxRow, coord.getY());
        maxCol = std::max(maxCol, coord.getX());
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
                                                    Vec2 &&anchorPoint) {
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

const Vec2 &Tetromino::getAnchorPoint() const noexcept { return anchorPoint_; }

const std::vector<Vec2> &Tetromino::getBody() const noexcept { return body_; }

unsigned Tetromino::getXorId() const noexcept {
    return static_cast<unsigned>(getShape());
}

const RotationIndex &Tetromino::getRotationIndex() const noexcept {
    return rotationIdx_;
}

const RotationIndex &Tetromino::getPrevRotationIndex() const noexcept {
    return prevRotationIdx_;
}

uint8_t Tetromino::getNumOfTests() const noexcept {
    return static_cast<uint8_t>(offsetData_.at(0).size());
}

std::unique_ptr<Tetromino> Tetromino::getNthOffset(uint8_t offsetIndex) const {
    std::unique_ptr<Tetromino> copy = std::make_unique<Tetromino>(*this);

    Vec2 offsetVal1 = offsetData_.at(prevRotationIdx_).at(offsetIndex - 1);
    Vec2 offsetVal2 = offsetData_.at(rotationIdx_).at(offsetIndex - 1);

    // Compute offset with offset data
    Vec2 offset = (offsetVal1 - offsetVal2);

    // Apply offset
    copy->anchorPoint_ += offset;

    return copy;
}

// #### Setters ####

void Tetromino::setAnchorPoint(const Vec2 &anchorPoint) {
    anchorPoint_ = anchorPoint;
}

// #### Tetromino Actions ####

void Tetromino::move(Direction direction, bool reverse) {
    switch (direction) {
    case Direction::Down:
        anchorPoint_.moveY(reverse ? -1 : +1);
        break;
    case Direction::Left:
        anchorPoint_.moveX(reverse ? +1 : -1);
        break;
    case Direction::Right:
        anchorPoint_.moveX(reverse ? -1 : +1);
        break;
    }
}

void Tetromino::rotate(bool rotateClockwise) {
    prevRotationIdx_ = rotationIdx_;
    rotationIdx_ += (rotateClockwise) ? 1 : -1;

    Vec2 center{0, 0}; // Convention : rotation center is always (0,0)

    for (Vec2 &coord : body_) {
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
