#ifndef GRID_CELL_HPP
#define GRID_CELL_HPP

#include <optional>

/**
 * @class GridCell
 *
 * @brief Represents a cell on the Tetris board, which can be in one of two
 * states:
 *  1. Holds a color, and therefore is not empty.
 *  2. Is empty and therefore has no color assigned.
 */
class GridCell final {
  private:
    std::optional<unsigned> colorId_;

  public:
    /**
     * @brief Checks if the cell is empty.
     *
     * @return Boolean.
     */
    virtual bool isEmpty() const;

    /**
     * @brief Gets the ColorId of the cell.
     *
     * @return The colorId.
     */
    virtual unsigned getColorId() const;

    /**
     * @brief Sets the ColorId of the cell.
     *
     * @param colorId The new ColorId.
     */
    virtual void setColorId(unsigned colorId);

    /**
     * @brief Clears the cell's ColorId.
     */
    virtual void setEmpty();
};

#endif
