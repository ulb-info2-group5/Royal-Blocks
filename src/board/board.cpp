#include "board.hpp"

#include "../tetromino/tetromino.hpp"
#include "../vec2/vec2.hpp"
#include "board_update.hpp"

#include <cstddef>
#include <memory>

// FIXME
#include <iostream>
using namespace std;

/*--------------------------------------------------
                    PRIVATE
--------------------------------------------------*/

// #### Helpers ####

GridCell &Board::at(int xCol, int yRow) { return getRow(yRow).at(xCol); }

std::array<GridCell, Board::width_> &Board::getRow(int yRow) {
    return grid_.at(getHeight() - 1 - yRow);
}

const std::array<GridCell, Board::width_> &Board::getRow(int yRow) const {
    return grid_.at(getHeight() - 1 - yRow);
}

void Board::dropRowsAbove(int yRow) {
    for (int y = yRow; y < getHeight() - 1; y++) {
        getRow(y) = getRow(y + 1);
    }

    emptyRow(getHeight() - 1);
}

bool Board::checkFullRow(int yRow) const {
    for (const auto &cell : getRow(yRow)) {
        if (cell.isEmpty()) {
            return false;
        }
    }

    return true;
}

bool Board::checkFullCol(int xCol) const {
    for (int yRow = getHeight() - 1; yRow >= 0; yRow--) {
        if (get(xCol, yRow).isEmpty()) {
            return false;
        }
    }

    return true;
}

void Board::emptyRow(int yRow) {
    for (GridCell &gridCell : getRow(yRow)) {
        gridCell.setEmpty();
    }
}

void Board::emptyCol(int xCol) {
    for (int yRow = getHeight() - 1; yRow >= 0; yRow--) {
        at(xCol, yRow).setEmpty();
    }
}

// FIXME: fix this, broken since we changed the way from matrix to cartesian
// indexing
void Board::gravity() {
    for (int xCoord = 0; xCoord < getWidth(); xCoord++) {
        int writeYCoord = getHeight() - 1;

        for (int yCoord = getHeight() - 1; yCoord >= 0; yCoord--) {
            if (!get(yCoord, xCoord).isEmpty()) {
                if (yCoord != writeYCoord) {
                    at(writeYCoord, xCoord) = at(yCoord, xCoord);
                    at(yCoord, xCoord).setEmpty();
                }
                writeYCoord--;
            }
        }
    }
}

/*--------------------------------------------------
                    PUBLIC
--------------------------------------------------*/

// #### Getters ####

const GridCell &Board::get(int xCol, int yRow) const {
    return getRow(yRow).at(xCol);
}

size_t Board::getWidth() const noexcept { return width_; }

size_t Board::getHeight() const noexcept { return height_; }

// #### Board Actions ####

void Board::placeTetromino(TetrominoPtr tetromino) {
    Vec2 anchor = tetromino->getAnchorPoint();

    for (const Vec2 &relativeCoord : tetromino->getBody()) {
        Vec2 absoluteCoord = anchor + relativeCoord;
        at(absoluteCoord.getX(), absoluteCoord.getY())
            .setColorId(tetromino->getColorId());
    }
}

bool Board::checkInGrid(Tetromino &tetromino) const {
    Vec2 anchor = tetromino.getAnchorPoint();
    for (const Vec2 &relativeCoord : tetromino.getBody()) {
        Vec2 absoluteCoord = relativeCoord + anchor;
        if (absoluteCoord.getX() < 0 || absoluteCoord.getX() >= getWidth()
            || absoluteCoord.getY() < 0 || absoluteCoord.getY() >= getHeight()
            || !(get(absoluteCoord.getX(), absoluteCoord.getY()).isEmpty())) {

            return false;
        }
    }

    return true;
}

// #### Update Board State ####

BoardUpdate Board::update() {
    BoardUpdate boardUpdate;

    for (int yRow = getHeight() - 1; yRow <= 0; yRow--) {
        if (checkFullRow(yRow)) {
            emptyRow(yRow);
            boardUpdate.incrementClearedRows();
            dropRowsAbove(yRow);
        }
    }

    return boardUpdate;
}
