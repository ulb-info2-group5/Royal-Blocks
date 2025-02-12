#ifndef TETROMINO_SHAPES_HPP
#define TETROMINO_SHAPES_HPP

#include "tetromino.hpp"

#include <iostream>

/**
 * @file tetromino_shapes.hpp
 *
 * @brief Contains all derivatives of the Tetromino abstract class, one for each
 * shape, as well as the TetrominoShape enum class to be passed to the Tetromino
 * factory.
 */

/*--------------------------------------------------
             TetrominoShapes
--------------------------------------------------*/

/**
 * @enum TetrominoShape
 *
 * @brief All possible shapes a tetromino can have.
 *
 * @note NumTetrominoShape is not an actual Shape, it is just there to avoid
 * having to hardcode the number of shapes in other parts of the code.
 */
enum class TetrominoShape {
    Z = 0,
    L,
    O,
    S,
    I,
    J,
    T,
    MiniTetromino,
    NumTetrominoShape,
};

// #### OUTPUT STREAM ####

/**
 * @brief Outputs a TetrominoShape to the given stream.
 *
 * @param os The output stream.
 * @param shape The TetrominoShape to output.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &os, TetrominoShape shape);

/*--------------------------------------------------
             Tetromino's Derivatives
--------------------------------------------------*/

// #### Z Shape ####

/**
 * @class TetrominoZ
 */
class TetrominoZ final : public ATetromino {
  public:
    /**
     * @brief TetrominoZ constructor.
     *
     * @param anchorPoint The TetrominoZ's anchor-point.
     */
    TetrominoZ(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoZ>(*this);
    }
};

// #### L Shape ####

/**
 * @class TetrominoL
 */
class TetrominoL final : public ATetromino {
  public:
    /**
     * @brief TetrominoL constructor.
     *
     * @param anchorPoint The TetrominoL's anchor-point.
     */
    TetrominoL(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoL>(*this);
    }
};

// #### O Shape ####

/**
 * @class TetrominoO
 */
class TetrominoO final : public ATetromino {
  public:
    /**
     * @brief TetrominoO constructor.
     *
     * @param anchorPoint The TetrominoO's anchor-point.
     */
    TetrominoO(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoO>(*this);
    }
};

// #### S Shape ####

/**
 * @class TetrominoS
 */
class TetrominoS final : public ATetromino {
  public:
    /**
     * @brief TetrominoS constructor.
     *
     * @param anchorPoint The TetrominoS's anchor-point.
     */
    TetrominoS(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoS>(*this);
    }
};

// #### I Shape ####

/**
 * @class TetrominoI
 */
class TetrominoI final : public ATetromino {
  public:
    /**
     * @brief TetrominoI constructor.
     *
     * @param anchorPoint The TetrominoI's anchor-point.
     */
    TetrominoI(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoI>(*this);
    }
};

// #### J Shape ####

/**
 * @class TetrominoJ
 */
class TetrominoJ final : public ATetromino {
  public:
    /**
     * @brief TetrominoJ constructor.
     *
     * @param anchorPoint The TetrominoJ's anchor-point.
     */
    TetrominoJ(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoJ>(*this);
    }
};

// #### T Shape ####

/**
 * @class TetrominoT
 */
class TetrominoT final : public ATetromino {
  public:
    /**
     * @brief TetrominoT constructor.
     *
     * @param anchorPoint The TetrominoT's anchor-point.
     */
    TetrominoT(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<TetrominoT>(*this);
    }
};

// #### MiniTetromino Shape ####

/**
 * @class MiniTetromino
 */
class MiniTetromino final : public ATetromino {
  public:
    /**
     * @brief MiniTetromino constructor.
     *
     * @param anchorPoint The MiniTetromino's anchor-point.
     */
    MiniTetromino(Vec2 &&anchorPoint);

    TetrominoPtr clone() const override {
        return make_clone<MiniTetromino>(*this);
    }
};

#endif
