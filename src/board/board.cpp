#include "board.hpp"

#include "../tetromino/tetromino.hpp"
#include "../vec2/vec2.hpp"
#include "board_update.hpp"
#include <memory>

/*--------------------------------------------------
                    PRIVATE
--------------------------------------------------*/

// #### Helpers ####

GridCell &Board::at(size_t rowIdx, size_t colIdx) {
    return grid_.at(rowIdx).at(colIdx);
}

std::array<GridCell, Board::width_> &Board::getY(size_t rowIdx) {
    return grid_.at(rowIdx);
}

void Board::dropRowsAbove(size_t rowIdx) {
    for (size_t i = rowIdx; i > 0; i--) {
        getY(i) = getY(i - 1);
    }

    emptyRow(0);
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
    for (GridCell &gridCell : getY(rowIdx)) {
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

/*--------------------------------------------------
                    PUBLIC
--------------------------------------------------*/

// #### Getters ####

const GridCell &Board::get(size_t rowIdx, size_t colIdx) const {
    return grid_.at(rowIdx).at(colIdx);
}

size_t Board::getWidth() const noexcept { return width_; }

size_t Board::getHeight() const noexcept { return height_; }

// #### Board Actions ####

void Board::placeTetromino(std::unique_ptr<Tetromino> tetromino) {
    const Vec2 anchor = tetromino->getAnchorPoint();

    for (const Vec2 &relativeCoord : tetromino->getBody()) {
        Vec2 absoluteCoord = anchor + relativeCoord;
        at(absoluteCoord.getY(), absoluteCoord.getX())
            .setColorId(tetromino->getXorId());
    }
}

bool Board::checkInGrid(Tetromino &tetromino) const {
    Vec2 anchor = tetromino.getAnchorPoint();
    for (const Vec2 &relativeCoord : tetromino.getBody()) {
        Vec2 absoluteCoord = relativeCoord + anchor;
        if (absoluteCoord.getX() < 0 || absoluteCoord.getX() >= getWidth()
            || absoluteCoord.getY() < 0 || absoluteCoord.getY() >= getHeight()
            || !get(absoluteCoord.getY(), absoluteCoord.getX()).isEmpty()) {
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
