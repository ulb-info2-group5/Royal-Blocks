#include "board.hpp"

#include "../tetromino/tetromino.hpp"
#include "../vec2/vec2.hpp"
#include "board_update.hpp"
#include "grid_cell.hpp"

#include <array>
#include <cstddef>
#include <memory>
#include <random>

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
    const int topRow = getHeight() - 1;

    for (int y = yRow; y < static_cast<int>(topRow); y++) {
        setRow(getRow(y + 1), y);
    }

    emptyRow(getHeight() - 1);
}

void Board::liftRowsFrom(int yRow) {
    const int topRow = getHeight() - 1;

    for (int y = topRow; y > static_cast<int>(yRow); y--) {
        setRow(getRow(y - 1), y);
    }

    emptyRow(yRow);
}

void Board::setPenaltyLine(std::array<GridCell, width_> &row) {
    constexpr int firstCol = 0;
    const int lastCol = getWidth() - 1;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(firstCol, lastCol);

    // The empty block in the row
    size_t emptyIndex = distrib(gen);

    // Fill all the GridCell with PenaltyBlocksColor except one (empty state)
    for (size_t xCol = 0; xCol < getWidth(); xCol++) {
        if (xCol == emptyIndex) {
            row.at(xCol).setEmpty();
        } else {
            row.at(xCol).setColorId(PenaltyBlocksColor);
        }
    }
}

void Board::setRow(const std::array<GridCell, width_> &row, size_t yRow) {
    getRow(yRow) = row;
}

bool Board::checkEmptyRow(int yRow) const {
    for (const GridCell &gridCell : getRow(yRow)) {
        if (!gridCell.isEmpty()) {
            return false;
        }
    }

    return true;
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

void Board::gravity() {
    for (int xCol = 0; xCol < static_cast<int>(getWidth()); xCol++) {
        int writeY = 0;

        for (int yRow = 0; yRow < static_cast<int>(getHeight()); yRow++) {
            if (!get(xCol, yRow).isEmpty()) {
                if (yRow != writeY) {
                    at(xCol, writeY) = at(xCol, yRow);
                    at(xCol, yRow).setEmpty();
                }
                writeY++;
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

// #### Board Actions ####

void Board::placeTetromino(TetrominoPtr tetromino) {
    Vec2 anchor = tetromino->getAnchorPoint();

    for (const Vec2 &relativeCoord : tetromino->getBody()) {
        Vec2 absoluteCoord = anchor + relativeCoord;
        at(absoluteCoord.getX(), absoluteCoord.getY())
            .setColorId(tetromino->getColorId());
    }
}

bool Board::checkInGrid(ATetromino &tetromino) const {
    Vec2 anchor = tetromino.getAnchorPoint();
    for (const Vec2 &relativeCoord : tetromino.getBody()) {
        Vec2 absoluteCoord = relativeCoord + anchor;
        if (absoluteCoord.getX() < 0
            || absoluteCoord.getX() >= static_cast<int>(getWidth())
            || absoluteCoord.getY() < 0
            || absoluteCoord.getY() >= static_cast<int>(getHeight())
            || !(get(absoluteCoord.getX(), absoluteCoord.getY()).isEmpty())) {

            return false;
        }
    }

    return true;
}

bool Board::check2By2Occupied(int x, int y) {
    constexpr int SQUARE_WIDTH = 2;

    bool ret = true;
    for (int xOffset = 0; xOffset < SQUARE_WIDTH; xOffset++)
        for (int yOffset = 0; yOffset < SQUARE_WIDTH; yOffset++) {
            if (get(x + xOffset, y + yOffset).isEmpty()) {
                ret = false;
            }
        };
    return ret;
}

void Board::empty2By2Square(int x, int y) {
    constexpr int SQUARE_WIDTH = 2;

    for (int xOffset = 0; xOffset < SQUARE_WIDTH; xOffset++)
        for (int yOffset = 0; yOffset < SQUARE_WIDTH; yOffset++) {
            at(x + xOffset, y + yOffset).setEmpty();
        }
}

void Board::destroy2By2Occupied() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, Board::getHeight()
                                                      * Board::getWidth());
    int tmp = distrib(gen);
    int startY = tmp / Board::getHeight();
    int startX = tmp % Board::getWidth();

    bool found2By2 = false;

    for (int yOffset = 0;
         yOffset < static_cast<int>(Board::getHeight() - 1) && !found2By2;
         yOffset++) {
        for (int xOffset = 0;
             xOffset < static_cast<int>(Board::getWidth() - 1) && !found2By2;
             xOffset++) {

            int x =
                (startX + xOffset) % static_cast<int>(Board::getWidth() - 1);
            int y =
                (startY + yOffset) % static_cast<int>(Board::getHeight() - 1);

            if (check2By2Occupied(x, y)) {
                found2By2 = true;
                empty2By2Square(x, y);
            }
        }
    }
}

// #### Penalty Lines ####

bool Board::receivePenaltyLines(size_t numPenaltyLines) {
    if (!checkEmptyRow(getHeight() - numPenaltyLines)) {
        return false;
    }

    constexpr int bottomRow = 0;
    // Lift rows from the bottom to make room for the penalty lines.
    // TODO: avoid for-loop and make liftRows take a numRows parameter
    // (algorithmically better)
    for (size_t lineCount = 0; lineCount < numPenaltyLines; lineCount++) {
        liftRowsFrom(static_cast<int>(bottomRow));
    }

    // Fill the newly freed lines with penalty lines.
    for (size_t penaltyLinesCount = 0; penaltyLinesCount < numPenaltyLines;
         penaltyLinesCount++) {
        setPenaltyLine(getRow(penaltyLinesCount));
    }

    return true;
}

// #### Update Board State ####

BoardUpdate Board::update() {
    BoardUpdate boardUpdate;

    for (int yRow = getHeight() - 1; yRow >= 0; yRow--) {
        if (checkFullRow(yRow)) {
            emptyRow(yRow);
            boardUpdate.incrementClearedRows();
            dropRowsAbove(yRow);
        }
    }

    return boardUpdate;
}
