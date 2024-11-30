#include "coordinate.hpp"

// #### Constructors  ####

Coordinate::Coordinate(int row, int col) : row_{row}, col_{col} {}

Coordinate::Coordinate(const Coordinate &other) = default;

Coordinate::Coordinate(Coordinate &&other) = default;

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

// #### Operators ####

bool Coordinate::operator==(const Coordinate &other) const {
    return getRow() == other.getRow() and getCol() == other.getCol();
}

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
