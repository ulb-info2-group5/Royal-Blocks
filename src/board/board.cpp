#include "board.hpp"

#include "../coordinate/coordinate.hpp"
#include "../tetromino/tetromino.hpp"
#include "board_update.hpp"
#include <memory>

// #### Internal helper ####

GridCell &Board::at(size_t rowIdx, size_t colIdx) {
    return grid_.at(rowIdx).at(colIdx);
}

std::array<GridCell, Board::width_> &Board::getRow(size_t rowIdx) {
    return grid_.at(rowIdx);
}

bool Board::checkFullRow(size_t rowIdx) const {
    for (size_t colIdx = 0; colIdx < getWidth(); colIdx++) {
        if (get(rowIdx, colIdx).isEmpty()) {
            return false;
        }
    }
    return true;
}

bool Board::checkFullCol(size_t colIdx) const {
    for (size_t rowIdx = 0; rowIdx < width_; rowIdx++) {
        if (get(rowIdx, colIdx).isEmpty()) {
            return false;
        }
    }
    return true;
}

void Board::emptyRow(size_t rowIdx) {
    for (GridCell &gridCell : getRow(rowIdx)) {
        gridCell.setEmpty();
    }
}

void Board::emptyCol(size_t colIdx) {
    for (size_t rowIdx = 0; rowIdx < getWidth(); rowIdx++) {
        at(rowIdx, colIdx).setEmpty();
    }
}

void Board::gravity() {
    for (int colIdx = 0; colIdx < getWidth(); colIdx++) {
        int writeRowIdx = getHeight() - 1;

        for (int rowIdx = getHeight() - 1; rowIdx >= 0; rowIdx--) {
            if (!get(rowIdx, colIdx).isEmpty()) {
                if (rowIdx != writeRowIdx) {
                    at(writeRowIdx, colIdx) = at(rowIdx, colIdx);
                    at(rowIdx, colIdx).setEmpty();
                }
                writeRowIdx--;
            }
        }
    }
}

BoardUpdate Board::update() {
    BoardUpdate boardUpdate;

    for (size_t rowIdx = 0; rowIdx < getHeight(); rowIdx++) {
        if (checkFullRow(rowIdx)) {
            emptyRow(rowIdx);
            boardUpdate.incrementDestroyedRows();
        }
    }

    for (size_t colIdx = 0; colIdx < getWidth(); colIdx++) {
        if (checkFullCol(colIdx)) {
            emptyCol(colIdx);
            boardUpdate.incrementDestroyedCols();
        }
    }

    return boardUpdate;
}

// #### Getters ####

const GridCell &Board::get(size_t rowIdx, size_t colIdx) const {
    return grid_.at(rowIdx).at(colIdx);
}

size_t Board::getWidth() const { return width_; }

size_t Board::getHeight() const { return height_; }

// #### Board Actions ####

void Board::placeTetromino(std::unique_ptr<Tetromino> tetromino) {
    const Coordinate anchor = tetromino->getAnchorPoint();

    for (const Coordinate &relativeCoord : tetromino->getBody()) {
        Coordinate absoluteCoord = anchor + relativeCoord;
        at(absoluteCoord.getRow(), absoluteCoord.getCol())
            .setColorId(tetromino->getColorId());
    }

    update();
}

bool Board::checkInGrid(Tetromino &tetromino) const {
    Coordinate anchor = tetromino.getAnchorPoint();
    for (const Coordinate &relativeCoord : tetromino.getBody()) {
        Coordinate absoluteCoord = relativeCoord + anchor;
        if (absoluteCoord.getCol() < 0 || absoluteCoord.getCol() >= getWidth()
            || absoluteCoord.getRow() < 0
            || absoluteCoord.getRow() >= getHeight()
            || !get(absoluteCoord.getRow(), absoluteCoord.getCol()).isEmpty()) {
            return false;
        }
    }
    return true;
}

void Board::debugPrint() {
    for (size_t rowIdx = 0; rowIdx < getHeight(); rowIdx++) {
        for (size_t colIdx = 0; colIdx < getWidth(); colIdx++) {
            std::cout << grid_.at(rowIdx).at(colIdx).isEmpty() << " ";
        }
        std::cout << std::endl;
    }
}
