#include "tetromino.hpp"

#include "tetromino_shapes.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

// #### Constructor ####

Tetromino::Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body)
    : anchorPoint_{std::move(anchorPoint)}, body_{std::move(body)} {

    if (body_.size() != 4) {
        throw std::invalid_argument(
            "All Tetrominos must be composed of 4 blocks");
    }

    Coordinate boundingBoxTopLeft{std::numeric_limits<int>::max(),
                                  std::numeric_limits<int>::max()};

    // Find top-left corner of smallest rectangle containing the Tetromino
    for (const Coordinate &coord : body_) {
        boundingBoxTopLeft.setRow(
            std::min(coord.getRow(), boundingBoxTopLeft.getRow()));
        boundingBoxTopLeft.setCol(
            std::min(coord.getCol(), boundingBoxTopLeft.getCol()));
    }

    for (Coordinate &coord : body_) {
        coord -= boundingBoxTopLeft;
    }

    for (const Coordinate &coord : body_) {
        width_ = std::max(width_, coord.getCol() + 1);
        height_ = std::max(height_, coord.getRow() + 1);
    }
}

Tetromino::Tetromino(const Tetromino &other) = default;

Tetromino::Tetromino(Tetromino &&other) = default;

// #### Destructor ####

Tetromino::~Tetromino() = default;

// #### Assignment Operators  ####

Tetromino &Tetromino::operator=(const Tetromino &other) = default;

Tetromino &Tetromino::operator=(Tetromino &&other) = default;

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

// #### Tetromino Actions ####

void Tetromino::rotate() {
    Coordinate boundingBoxTopLeft{std::numeric_limits<int>::max(),
                                  std::numeric_limits<int>::max()};

    Coordinate center{height_ / 2, width_ / 2};

    // Find top-left corner of smallest rectangle containing the Tetromino
    for (Coordinate &coord : body_) {
        coord.rotateClockwiseAround(center);

        boundingBoxTopLeft.setRow(
            std::min(coord.getRow(), boundingBoxTopLeft.getRow()));
        boundingBoxTopLeft.setCol(
            std::min(coord.getCol(), boundingBoxTopLeft.getCol()));
    }

    for (Coordinate &coord : body_) {
        coord -= boundingBoxTopLeft;
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
