#include "tetromino.hpp"

#include "tetromino_shapes.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

// #### Constructors ####

Tetromino::Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body)
    : anchorPoint_{std::move(anchorPoint)}, body_{std::move(body)} {

    if (body_.size() != 4) {
        throw std::invalid_argument(
            "All Tetrominos must be composed of 4 blocks");
    }

    for (const Coordinate &coord : body_) {
        width_ = std::max(width_, coord.getCol());
        height_ = std::max(height_, coord.getRow());
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
        ret = std::make_unique<TetrominoT>(std::move(anchorPoint));
        break;
    case (TetrominoShape::J):
        ret = std::make_unique<TetrominoJ>(std::move(anchorPoint));
        break;
    case (TetrominoShape::T):
        ret = std::make_unique<TetrominoT>(std::move(anchorPoint));
        break;
    default:
        std::cerr << "Unknown TetrominoShape" << std::endl;
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

void Tetromino::tryRotate() {
    // TODO: this function should call checkInBoard (not written yet) method
    // with the just moved Tetromino, and then only if checkInBoard returned
    // true: apply/validate the move on the self

    int minCol = std::numeric_limits<int>::max();
    int minRow = std::numeric_limits<int>::max();

    Coordinate center{height_ / 2, width_ / 2};

    for (Coordinate &coord : body_) {
        // Translate the coordinate by the ((rotation center)->(0,0))) vector
        Coordinate translatedCoordinate{
            coord.getRow() - center.getRow(),
            coord.getCol() - center.getCol(),
        };

        // Matrix coordinate system to cartesian (flip the y/row axis)
        translatedCoordinate.setRow(-1 * translatedCoordinate.getRow());

        // 90-degree clockwise rotation
        Coordinate rotatedCoordinate{-translatedCoordinate.getCol(),
                                     translatedCoordinate.getRow()};

        // Go back to matrix coordinate system
        rotatedCoordinate.setRow(-1 * rotatedCoordinate.getRow());

        // Translate back to the original coordinate space
        rotatedCoordinate += center;

        // Update current coordinate to the rotated one
        coord = rotatedCoordinate;

        minRow = std::min(coord.getRow(), minRow);
        minCol = std::min(coord.getCol(), minCol);
    }

    // Translate the rotated shape to align with top-left corner
    for (Coordinate &coord : body_) {
        coord.setRow(coord.getRow() - minRow);
        coord.setCol(coord.getCol() - minCol);
    }

    std::swap(height_, width_);
}

void Tetromino::tryMove(Direction direction) {
    // TODO: this function should call checkInBoard (not written yet) method
    // with the just moved Tetromino, and then only if checkInBoard returned
    // true: apply/validate the move on the self
    switch (direction) {
    case Direction::down:
        anchorPoint_.setRow(anchorPoint_.getRow() - 1);
        break;
    case Direction::left:
        anchorPoint_.setCol(anchorPoint_.getCol() - 1);
        break;
    case Direction::right:
        anchorPoint_.setCol(anchorPoint_.getCol() + 1);
        break;
    }
}

// #### Debug ####

void Tetromino::debugPrint() const {
    std::cout << "{ ";
    for (const Coordinate &c : body_) {
        std::cout << "(" << c.getRow() << ", " << c.getCol() << ") ";
    }
    std::cout << "}" << std::endl;
}
