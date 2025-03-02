#ifndef GRID_CELL_HPP
#define GRID_CELL_HPP

#include <nlohmann/json.hpp>

#include <optional>

/**
 * @class GridCell
 *
 * @brief Represents a cell on the Tetris board, which can be in one of two
 * states:
 *  1. Holds a color, and therefore is not empty.
 *  2. Is empty and therefore has no color assigned.
 */
class GridCell {
  private:
    std::optional<unsigned> colorId_;

  public:
    // #### Constructors ####

    GridCell() = default;
    GridCell(const GridCell &) = default;
    GridCell(GridCell &&) = default;

    // #### Assignment ####

    GridCell &operator=(const GridCell &) = default;
    GridCell &operator=(GridCell &&) = default;

    // #### Destructor ####

    ~GridCell();

    // #### Getters ####

    /**
     * @brief Checks if the cell is empty.
     *
     * @return Boolean.
     */
    bool isEmpty() const noexcept;

    /**
     * @brief Gets the ColorId of the cell.
     *
     * @return The colorId.
     */
    unsigned getColorId() const;

    // #### Setters ####

    /**
     * @brief Sets the ColorId of the cell.
     *
     * @param colorId The new ColorId.
     */
    void setColorId(unsigned colorId) noexcept;

    /**
     * @brief Clears the cell's ColorId.
     */
    void setEmpty() noexcept;

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const {
        nlohmann::json j;
        if (colorId_) {
            j["colorId"] = *colorId_;
        } else {
            j["colorId"] = nullptr;
        }
        return j;
    }

    void deserialize(const nlohmann::json &j) {
        if (j.contains("colorId") && !j["colorId"].is_null()) {
            colorId_ = j.at("colorId").get<unsigned>();
        } else {
            colorId_ = std::nullopt;
        }
    }
};

#endif
