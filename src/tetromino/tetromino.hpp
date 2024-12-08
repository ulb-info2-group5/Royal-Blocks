#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../coordinate/coordinate.hpp"
#include "rotation_index/rotation_index.hpp"

#include <cstdint>
#include <memory>
#include <vector>

enum class TetrominoShape;

class TetrominoTest;

/**
 * @enum Direction
 *
 * @brief The three directions in which a Tetromino can be moved: left, right,
 * down.
 */
enum class Direction { Left, Right, Down };

/**
 * @class Tetromino
 *
 * @brief This class represents an abstract Tetromino (piece in Tetris), it
 * supports two rotation algorithms:
 *  - Very basic rotation algorithm which just rotate each tile around the
 *      predefined center of rotation
 *  - SRS | Super Rotation System SRS, cf. https://tetris.fandom.com/wiki/SRS
 *      @note The process of determining which offset-test is passed must be
 *      implemented outside of this class.
 */
class Tetromino {
  private:
    size_t width_ = 0;
    size_t height_ = 0;
    TetrominoShape shape_;
    Coordinate anchorPoint_;
    std::vector<Coordinate> body_;

    // #### SRS-related ####

    RotationIndex rotationIdx_;
    RotationIndex prevRotationIdx_;
    const std::vector<std::vector<Coordinate>> &offsetData_;

  protected:
    // #### SRS Offsets Data Constants ####

    static const std::vector<std::vector<Coordinate>> O_OFFSET_DATA;
    static const std::vector<std::vector<Coordinate>> I_OFFSET_DATA;
    static const std::vector<std::vector<Coordinate>> ZLSJT_OFFSET_DATA;

    // #### Constructor ####

    /**
     * @brief Protected constructor for the Tetromino class.
     *
     * This constructor is intended to be used exclusively by derived
     * classes of Tetromino.
     *
     * @param anchorPoint The coordinate of the Tetromino's anchor point within
     * the Tetris grid.
     * @param body A vector of coordinates representing the positions of each
     * tile relative to the rotation center.
     * @param offsetData A reference to a matrix of Coordinates being the
     * offset data used for implementing SRS on this shape of Tetromino,
     * i.e. ZLSJT_OFFSET_DATA.
     * @param shape The shape of the Tetromino.
     * */
    Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body,
              const std::vector<std::vector<Coordinate>> &offsetData,
              TetrominoShape shape);

  public:
    // #### Copy Constructor ####

    /**
     * @brief Tetromino's copy constructor.
     */
    Tetromino(const Tetromino &other);

    // #### Destructor ####

    /**
     * @brief Tetromino's destructor.
     */
    virtual ~Tetromino();

    // #### Factory ####

    /**
     * @brief Tetromino factory
     *
     * @param shape The Tetromino's shape.
     * @param anchorPoint The Tetromino's rotation center's coordinate relative
     * to the tetris grid.
     *
     * @return A unique pointer to the newly created Tetromino object.
     */
    static std::unique_ptr<Tetromino> makeTetromino(TetrominoShape shape,
                                                    Coordinate &&anchorPoint);

    // #### Getters ####

    /**
     * @brief Returns the Tetromino's width.
     *
     * @return The width.
     */
    virtual size_t getWidth() const noexcept;

    /**
     * @brief Returns the Tetromino's height.
     *
     * @return The height.
     */
    virtual size_t getHeight() const noexcept;

    /**
     * @brief Returns the Tetromino's shape.
     *
     * @return The shape.
     */
    virtual TetrominoShape getShape() const noexcept;

    /**
     * @brief Returns the Tetromino's Coordinate.
     *
     * @return The anchor-point.
     */
    virtual const Coordinate &getAnchorPoint() const noexcept;

    /**
     * @brief Returns the Tetromino's body.
     *
     * @return The body.
     */
    virtual const std::vector<Coordinate> &getBody() const noexcept;

    /**
     * @brief Returns the Tetromino's colorId.
     *
     * @return The colorId.
     */
    virtual unsigned getColorId() const noexcept;

    /**
     * @brief Returns the Tetromino's rotation-index.
     *
     * @return The rotation-index.
     */
    virtual const RotationIndex &getRotationIndex() const noexcept;

    /**
     * @brief Returns the Tetromino's previous rotation index.
     *
     * @return The previous rotation-index.
     */
    virtual const RotationIndex &getPrevRotationIndex() const noexcept;

    /**
     * @brief Returns the number of offset-tests that this Tetromino can do
     * (SRS).
     *
     * @return The number of tests as a uint8_t
     */
    virtual uint8_t getNumOfTests() const noexcept;

    /**
     * @brief Creates and returns a unique pointer to a new Tetromino,
     * offset by the specified offsetIndex index using SRS (Super Rotation
     * System).
     *
     * @param offsetIndex The offset index (starting from 1).
     *                    Determines the offset to apply to the Tetromino.
     *
     * @return A unique pointer to the newly created Tetromino, adjusted
     *         by the specified offset.
     */
    virtual std::unique_ptr<Tetromino>
    getNthOffset(uint8_t offsetIndex) const noexcept;

    // #### Setters ####

    /**
     * @brief Sets the Tetromino's anchor-point.
     *
     * @param anchorPoint The new anchor-point.
     */
    virtual void setAnchorPoint(const Coordinate &anchorPoint);

    // #### Tetromino Actions ####

    /**
     * @brief Moves the Tetromino in the given direction.
     *
     * @param direction The direction to move the Tetromino.
     * @param reverse If true, moves the Tetromino in the opposite direction.
     */
    virtual void move(Direction direction, bool reverse = false);

    /**
     * @brief Rotates the Tetromino around it rotation-center (Without SRS).
     *
     * @param rotateClockwise If true, rotates the Tetromino clockwise;
     * otherwise, rotates it counterclockwise.
     */
    virtual void rotate(bool rotateClockwise);

    // #### Comparisons Operators ####

    /**
     * @brief Compares two Tetromino objects.
     *
     * @param other The Tetromino to compare with.
     * @return True if the two Tetrominoes are equal; otherwise, false.
     */
    virtual bool operator==(const Tetromino &other) const;

    /**
     * @brief Compares two Tetromino objects.
     *
     * @param other The Tetromino to compare with.
     * @return True if the two Tetrominoes are different; otherwise, false.
     */
    virtual bool operator!=(const Tetromino &other) const;

    // #### Output Stream ####

    /**
     * @brief Outputs the Tetromino to a stream.
     *
     * @param os The output stream.
     * @param tetromino The Tetromino to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os,
                                    const Tetromino &tetromino);

    // #### Test Fixture Class ####

    friend TetrominoTest;
};

#endif
