#include "board.hpp"

#include "../tetromino/tetromino.hpp"
#include "../vec2/vec2.hpp"
#include "board_update.hpp"

#include <memory>

/*--------------------------------------------------
                    PRIVATE
--------------------------------------------------*/

// #### Helpers ####

GridCell &Board::at(size_t xCoord, size_t yCoord) {
    return grid_.at(height_ - 1 - yCoord).at(xCoord);
}

std::array<GridCell, Board::width_> &Board::getRow(size_t yCoord) {
    return grid_.at(height_ - 1 - yCoord);
}

const std::array<GridCell, Board::width_> &Board::getRow(size_t yCoord) const {
    return grid_.at(yCoord);
}

void Board::dropRowsAbove(size_t yCoord) {
    for (size_t i = yCoord; i > 0; i--) {
        getRow(i) = getRow(i - 1);
    }

    emptyRow(height_ - 1);
}

bool Board::checkFullRow(size_t yCoord) const {
    for (const auto &cell : getRow(yCoord)) {
        if (cell.isEmpty()) {
            return false;
        }
    }

    return true;
}

bool Board::checkFullCol(size_t xCoord) const {
    for (size_t yCoord = height_ - 1; yCoord >= 0; yCoord--) {
        if (get(yCoord, xCoord).isEmpty()) {
            return false;
        }
    }

    return true;
}

void Board::emptyRow(size_t yCoord) {
    for (GridCell &gridCell : getRow(yCoord)) {
        gridCell.setEmpty();
    }
}

void Board::emptyCol(size_t xCoord) {
    for (size_t yCoord = 0; yCoord < height_ - 1; yCoord++) {
        at(yCoord, xCoord).setEmpty();
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

const GridCell &Board::get(size_t xCoord, size_t yCoord) const {
    return grid_.at(height_ - 1 - yCoord).at(xCoord);
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
            || !get(absoluteCoord.getX(), absoluteCoord.getY()).isEmpty()) {

            return false;
        }
    }

    return true;
}

// #### Update Board State ####

BoardUpdate Board::update() {
    BoardUpdate boardUpdate;

    for (size_t rowIdx = 0; rowIdx < getHeight(); rowIdx++) {
        if (checkFullRow(rowIdx)) {
            emptyRow(rowIdx);
            boardUpdate.incrementClearedRows();
            dropRowsAbove(rowIdx);
        }
    }

    return boardUpdate;
}
