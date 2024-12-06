#include "board.hpp"

#include "../coordinate/coordinate.hpp"
#include "../tetromino/tetromino.hpp"

// #### Internal helper ####
GridCell &Board::at(size_t rowIdx, size_t colIdx) {
    return grid_[rowIdx][colIdx];
}

std::array<GridCell, Board::width_> &Board::getRow(size_t row) {
    return grid_[row];
}

bool Board::checkFullRow(size_t rowIdx) {
    for (size_t colIdx = 0; colIdx < width_; colIdx++) {
        if (get(rowIdx, colIdx).isEmpty()) {
            return false;
        }
    }
    return true;
}

void Board::emptyRow(int rowIdx) {
    for (GridCell &gridCell : getRow(rowIdx)) {
        gridCell.setEmpty();
    }
}

void Board::gravity() {
    for (size_t colIdx = 0; colIdx < width_; colIdx++) {
        size_t writeRowIdx = height_ - 1;

        for (size_t rowIdx = height_ - 1; rowIdx >= 0; rowIdx--) {
            if (!get(rowIdx, colIdx).isEmpty()) {
                at(writeRowIdx, colIdx) = get(rowIdx, colIdx);
                at(rowIdx, colIdx).setEmpty();
                writeRowIdx--;
            }

            if (rowIdx == 0) break;
        }
    }
}

void Board::update() {
    for (size_t rowIdx = 0; rowIdx < height_ - 1; rowIdx++) {
        if (checkFullRow(rowIdx)) {
            emptyRow(rowIdx);
        }
    }

    gravity();
}

// #### Getters ####

const GridCell &Board::get(size_t row, size_t col) { return at(row, col); }

size_t Board::getWidth() { return width_; }

size_t Board::getHeight() { return height_; }

// #### Board Actions ####

void Board::placeTetromino(const Tetromino &tetromino) {
    const Coordinate anchor = tetromino.getAnchorPoint();
    for (const Coordinate &relativeCoord : tetromino.getBody()) {
        Coordinate absoluteCoord = anchor + relativeCoord;
        at(absoluteCoord.getRow(), absoluteCoord.getCol())
            .setColorId(tetromino.getColorId());
    }

    update();
}

bool Board::checkInGrid(Tetromino &tetromino) {
    Coordinate anchor = tetromino.getAnchorPoint();
    for (const Coordinate &relativeCoord : tetromino.getBody()) {
        Coordinate absoluteCoord = relativeCoord + anchor;
        if (absoluteCoord.getCol() < 0 || absoluteCoord.getCol() >= width_
            || absoluteCoord.getRow() < 0 || absoluteCoord.getRow() >= height_
            || !get(absoluteCoord.getRow(), absoluteCoord.getCol()).isEmpty()) {
            return false;
        }
    }
    return true;
}
