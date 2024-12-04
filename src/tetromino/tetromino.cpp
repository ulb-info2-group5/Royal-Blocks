#include "tetromino.hpp"

#include "../coordinate/coordinate.hpp"
#include "tetromino_shapes.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

// #### Kick Data Constants ####
// TODO: define the kick data's
const std::vector<std::vector<Coordinate>> Tetromino::O_OFFSET_DATA = {
    {{0, 0}}};
const std::vector<std::vector<Coordinate>> Tetromino::I_OFFSET_DATA = {
    {{0, 0}}};
const std::vector<std::vector<Coordinate>> Tetromino::ZLSJT_OFFSET_DATA = {
    {{0, 0}}};

// #### Constructor ####

Tetromino::Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body,
                     const std::vector<std::vector<Coordinate>> &offsetData,
                     TetrominoShape shape)
    : anchorPoint_{std::move(anchorPoint)}, body_{std::move(body)},
      offsetData_(offsetData), shape_(shape) {

    if (body_.size() != 4) {
        throw std::invalid_argument(
            "All Tetrominos must be composed of 4 blocks");
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

Tetromino::Tetromino(const Tetromino &other) = default;

Tetromino::Tetromino(Tetromino &&other) = default;

// #### Destructor ####

Tetromino::~Tetromino() = default;

// #### Assignment Operators  ####

// Tetromino &Tetromino::operator=(const Tetromino &other) = default;
// Tetromino &Tetromino::operator=(Tetromino &&other) = default;

// #### Factory ####

std::unique_ptr<Tetromino> Tetromino::makeTetromino(TetrominoShape shape,
                                                    Coordinate &&anchorPoint) {
    if (shape == TetrominoShape::NUM_TETROMINOSHAPE) {
        throw std::runtime_error(
            "shape must be different from NUM_TETROMINOSHAPE");
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

int Tetromino::getWidth() const noexcept { return width_; }

int Tetromino::getHeight() const noexcept { return height_; }

TetrominoShape Tetromino::getShape() const noexcept { return shape_; }

const Coordinate &Tetromino::getAnchorPoint() const noexcept {
    return anchorPoint_;
}

const std::vector<Coordinate> &Tetromino::getBody() const noexcept {
    return body_;
}

std::unique_ptr<Tetromino>
Tetromino::getNthKick(uint8_t kickIndex) const noexcept {
    std::unique_ptr<Tetromino> copy = std::make_unique<Tetromino>(*this);

    Coordinate offsetVal1 = offsetData_[oldRotationIdx_][kickIndex];
    Coordinate offsetVal2 = offsetData_[rotationIdx_][kickIndex];

    // Compute kick with offset data
    Coordinate kick = (offsetVal1 - offsetVal2);

    // Apply kick
    copy->anchorPoint_ += kick;

    return copy;
}

// #### Tetromino Actions ####

void Tetromino::rotate(bool rotateClockwise) {
    oldRotationIdx_ = rotationIdx_;
    rotationIdx_ += (rotateClockwise) ? 1 : -1;

    Coordinate center{0, 0}; // convention that rotation center is always (0,0)

    for (Coordinate &coord : body_) {
        coord.rotateAround(center, rotateClockwise);
    }

    std::swap(height_, width_);
}

void Tetromino::move(Direction direction) {
    switch (direction) {
    case Direction::down:
        anchorPoint_.moveRow(1);
        break;
    case Direction::left:
        anchorPoint_.moveCol(-1);
        break;
    case Direction::right:
        anchorPoint_.moveCol(+1);
        break;
    }
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
