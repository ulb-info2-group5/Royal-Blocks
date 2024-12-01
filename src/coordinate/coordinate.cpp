#include "coordinate.hpp"

// #### Constructors  ####

Coordinate::Coordinate() = default;

Coordinate::Coordinate(int row, int col) : row_{row}, col_{col} {}

Coordinate::Coordinate(const Coordinate &other) = default;

Coordinate::Coordinate(Coordinate &&other) = default;

// #### Destructors  ####

Coordinate::~Coordinate() = default;

// #### Assignment Operators  ####

Coordinate &Coordinate::operator=(const Coordinate &other) = default;

Coordinate &Coordinate::operator=(Coordinate &&other) = default;

// #### Getters ####

int Coordinate::getRow() const noexcept { return row_; }

int Coordinate::getCol() const noexcept { return col_; }

// #### Setters ####

void Coordinate::setRow(int row) { row_ = row; }

void Coordinate::setCol(int col) { col_ = col; }

void Coordinate::moveRow(int row) { setRow(getRow() + row); }

void Coordinate::moveCol(int col) { setCol(getCol() + col); }

// #### Comparison Operators ####

bool Coordinate::operator==(const Coordinate &other) const {
    return getRow() == other.getRow() and getCol() == other.getCol();
}

bool Coordinate::operator!=(const Coordinate &other) const {
    return !(getRow() == other.getRow() and getCol() == other.getCol());
}

// #### Arithmetic Operators ####

Coordinate Coordinate::operator+(const Coordinate &other) const {
    return Coordinate{getRow(), getCol()} += other;
}

Coordinate &Coordinate::operator+=(const Coordinate &other) {
    moveCol(other.getCol());
    moveRow(other.getRow());
    return *this;
}

Coordinate Coordinate::operator-(const Coordinate &other) const {
    return Coordinate{getRow(), getCol()} -= other;
}

Coordinate &Coordinate::operator-=(const Coordinate &other) {
    moveCol(-other.getCol());
    moveRow(-other.getRow());
    return *this;
}

Coordinate Coordinate::operator-() const {
    return Coordinate{-getRow(), -getCol()};
}

// #### Rotation #####

const Coordinate &
Coordinate::rotateClockwiseAround(const Coordinate &rotationCenter) {
    // Translate the coordinate by the ((rotationCenter)->(0,0))) vector
    int translatedRow = row_ - rotationCenter.getRow();
    int translatedCol = col_ - rotationCenter.getCol();

    // Matrix coordinate system to cartesian (flip the y/row axis)
    translatedRow = -translatedRow;

    // Perform the 90-degree clockwise rotation
    int rotatedRow = -translatedCol;
    int rotatedCol = translatedRow;

    // Go back to matrix coordinate system
    rotatedRow = -rotatedRow;

    // Translate back to the original coordinate space
    row_ = rotatedRow + rotationCenter.getRow();
    col_ = rotatedCol + rotationCenter.getCol();

    return *this;
}

// #### Output Stream ####

std::ostream &operator<<(std::ostream &os, const Coordinate &coord) {
    os << "(" << coord.getRow() << ", " << coord.getCol() << ")";
    return os;
}
