#include "tetromino.hpp"

#include "../coordinate/coordinate.hpp"
#include "tetromino_shapes.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

// #### Kick Data Constants ####
// TODO: define the kick data's
const std::vector<std::vector<Coordinate>> Tetromino::O_KICK_DATA = {{{0, 0}}};
const std::vector<std::vector<Coordinate>> Tetromino::I_KICK_DATA = {{{0, 0}}};
const std::vector<std::vector<Coordinate>> Tetromino::ZLSJT_KICK_DATA = {
    {{0, 0}}};

// #### Constructor ####

Tetromino::Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body,
                     const std::vector<std::vector<Coordinate>> &kickData)
    : anchorPoint_{std::move(anchorPoint)}, body_{std::move(body)},
      kickData_(kickData) {

    if (body_.size() != 4) {
        throw std::invalid_argument(
            "All Tetrominos must be composed of 4 blocks");
    }

    int minRow, minCol = std::numeric_limits<int>::max();
    int maxRow, maxCol = std::numeric_limits<int>::min();

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

const Coordinate &Tetromino::getAnchorPoint() const noexcept {
    return anchorPoint_;
}

const std::vector<Coordinate> &Tetromino::getBody() const noexcept {
    return body_;
}

std::unique_ptr<Tetromino>
Tetromino::getNthKick(uint8_t kickIndex) const noexcept {
    // copy *this into a unique ptr
    // get the kickdatas for old and current rotationIndexes
    // calculate the kickdata for oldRotationIndex to current rotationIndex
    // apply it to the copy
    // retun the copy
}

// #### Tetromino Actions ####

void Tetromino::rotate(bool rotateClockwise) {
    rotationIdx_ += (rotateClockwise) ? 1 : -1;
    Coordinate boundingBoxTopLeft{std::numeric_limits<int>::max(),
                                  std::numeric_limits<int>::max()};

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
        std::cout << coord;
    }
    std::cout << "}";
    return os;
}
