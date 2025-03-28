#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../vec2/vec2.hpp"
#include "rotation_index/rotation_index.hpp"

#include <nlohmann/json.hpp>

#include <concepts>
#include <cstdint>
#include <memory>
#include <vector>

enum class TetrominoShape;
class TetrominoTest;
class ATetromino;
using TetrominoPtr = std::unique_ptr<ATetromino>;

/**
 * @enum TetrominoMove
 *
 * @brief The three directions in which a Tetromino can be moved: left, right,
 * down.
 */
enum class TetrominoMove { Left, Right, Down };

/**
 * @class ATetromino
 *
 * @brief This class represents an abstract Tetromino (piece in Tetris), it
 * supports two rotation algorithms:
 *  - Very basic rotation algorithm which just rotate each tile around the
 *      predefined center of rotation
 *  - SRS | Super Rotation System SRS, cf. https://tetris.fandom.com/wiki/SRS
 *      @note The process of determining which offset-test is passed must be
 *      implemented outside of this class.
 */
class ATetromino {
  public:
    constexpr static size_t MAX_DIMENSION = 4;

  private:
    size_t width_ = 0;
    size_t height_ = 0;
    TetrominoShape shape_;
    Vec2 anchorPoint_;
    std::vector<Vec2> body_;

    // #### SRS-related ####

    RotationIndex rotationIdx_;
    RotationIndex prevRotationIdx_;
    const std::vector<std::vector<Vec2>> *offsetData_;

  protected:
    // #### SRS Offsets Data Constants ####

    static const std::vector<std::vector<Vec2>> O_OFFSET_DATA;
    static const std::vector<std::vector<Vec2>> I_OFFSET_DATA;
    static const std::vector<std::vector<Vec2>> ZLSJT_OFFSET_DATA;

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
     * @param offsetData A reference to a matrix of Vec2s being the
     * offset data used for implementing SRS on this shape of Tetromino,
     * e.g. ZLSJT_OFFSET_DATA.
     * @param shape The shape of the Tetromino.
     * */
    ATetromino(Vec2 &&anchorPoint, std::vector<Vec2> &&body,
               const std::vector<std::vector<Vec2>> *offsetData,
               TetrominoShape shape);

    // #### Cloning Tetromino's derivatives #####

    template <typename Derived>
        requires std::derived_from<Derived, ATetromino>
    static TetrominoPtr make_clone(const ATetromino &tetromino) {
        const Derived *pDerived = dynamic_cast<const Derived *>(&tetromino);
        if (!pDerived) {
            return nullptr;
        }

        return std::make_unique<Derived>(*pDerived);
    }

  public:
    // #### Copy Constructor ####

    ATetromino() = delete;
    ATetromino(const ATetromino &other) = default;
    ATetromino(ATetromino &&) = default;

    // #### Assignment ####

    ATetromino &operator=(const ATetromino &) = default;
    ATetromino &operator=(ATetromino &&) = default;

    // #### Destructor ####

    virtual ~ATetromino() = default;

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
    static TetrominoPtr makeTetromino(TetrominoShape shape, Vec2 &&anchorPoint);

    // #### Getters ####

    /**
     * @brief Returns the Tetromino's width.
     *
     * @return The width.
     */
    size_t getWidth() const noexcept;

    /**
     * @brief Returns the Tetromino's height.
     *
     * @return The height.
     */
    size_t getHeight() const noexcept;

    /**
     * @brief Returns the Tetromino's shape.
     *
     * @return The shape.
     */
    TetrominoShape getShape() const noexcept;

    /**
     * @brief Returns the Tetromino's Vec2.
     *
     * @return The anchor-point.
     */
    const Vec2 &getAnchorPoint() const noexcept;

    /**
     * @brief Returns the Tetromino's body.
     *
     * @return The body.
     */
    const std::vector<Vec2> &getBody() const noexcept;

    /**
     * @brief Returns the Tetromino's colorId.
     *
     * @return The colorId.
     */
    unsigned getColorId() const noexcept;

    /**
     * @brief Returns the Tetromino's rotation-index.
     *
     * @return The rotation-index.
     */
    const RotationIndex &getRotationIndex() const noexcept;

    /**
     * @brief Returns the Tetromino's previous rotation index.
     *
     * @return The previous rotation-index.
     */
    const RotationIndex &getPrevRotationIndex() const noexcept;

    /**
     * @brief Returns the number of offset-tests that this Tetromino can do
     * (SRS).
     *
     * @return The number of tests as a uint8_t
     */
    uint8_t getNumOfTests() const noexcept;

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
    TetrominoPtr getNthOffset(uint8_t offsetIndex) const;

    // #### Setters ####

    /**
     * @brief Sets the Tetromino's anchor-point.
     *
     * @param anchorPoint The new anchor-point.
     */
    void setAnchorPoint(const Vec2 &anchorPoint);

    // #### Tetromino Actions ####

    /**
     * @brief Moves the Tetromino in the given direction.
     *
     * @param tetrominoMove The direction to move the Tetromino.
     * @param reverse If true, moves the Tetromino in the opposite direction.
     */
    void move(TetrominoMove tetrominoMove, bool reverse = false);

    /**
     * @brief Rotates the Tetromino around it rotation-center (Without SRS).
     *
     * @param rotateClockwise If true, rotates the Tetromino clockwise;
     * otherwise, rotates it counterclockwise.
     */
    void rotate(bool rotateClockwise);

    // #### Comparisons Operators ####

    /**
     * @brief Compares two Tetromino objects.
     *
     * @param other The Tetromino to compare with.
     * @return True if the two Tetrominoes are equal; otherwise, false.
     */
    bool operator==(const ATetromino &other) const;

    /**
     * @brief Compares two Tetromino objects.
     *
     * @param other The Tetromino to compare with.
     * @return True if the two Tetrominoes are different; otherwise, false.
     */
    bool operator!=(const ATetromino &other) const;

    // #### Cloning Tetromino's derivatives ####

    virtual TetrominoPtr clone() const = 0;

    // #### Output Stream ####

    /**
     * @brief Outputs the Tetromino to a stream.
     *
     * @param os The output stream.
     * @param tetromino The Tetromino to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os,
                                    const ATetromino &tetromino);

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const {
        nlohmann::json j_body = nlohmann::json::array();
        for (const auto &vec : body_) {
            j_body.push_back(vec.serialize());
        }

        return nlohmann::json{
            {"anchorPoint", anchorPoint_.serialize()},
            {"body", j_body},
            {"colorId", getColorId()},
        };
    }

    /* ------------------------------------------------
     *          Test Fixture Class
     * ------------------------------------------------*/

    friend TetrominoTest;
};

#endif
