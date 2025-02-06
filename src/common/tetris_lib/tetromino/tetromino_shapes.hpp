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
class TetrominoZ final : public Tetromino {
  public:
    /**
     * @brief TetrominoZ constructor.
     *
     * @param anchorPoint The TetrominoZ's anchor-point.
     */
    TetrominoZ(Vec2 &&anchorPoint);
};

// #### L Shape ####

/**
 * @class TetrominoL
 */
class TetrominoL final : public Tetromino {
  public:
    /**
     * @brief TetrominoL constructor.
     *
     * @param anchorPoint The TetrominoL's anchor-point.
     */
    TetrominoL(Vec2 &&anchorPoint);
};

// #### O Shape ####

/**
 * @class TetrominoO
 */
class TetrominoO final : public Tetromino {
  public:
    /**
     * @brief TetrominoO constructor.
     *
     * @param anchorPoint The TetrominoO's anchor-point.
     */
    TetrominoO(Vec2 &&anchorPoint);
};

// #### S Shape ####

/**
 * @class TetrominoS
 */
class TetrominoS final : public Tetromino {
  public:
    /**
     * @brief TetrominoS constructor.
     *
     * @param anchorPoint The TetrominoS's anchor-point.
     */
    TetrominoS(Vec2 &&anchorPoint);
};

// #### I Shape ####

/**
 * @class TetrominoI
 */
class TetrominoI final : public Tetromino {
  public:
    /**
     * @brief TetrominoI constructor.
     *
     * @param anchorPoint The TetrominoI's anchor-point.
     */
    TetrominoI(Vec2 &&anchorPoint);
};

// #### J Shape ####

/**
 * @class TetrominoJ
 */
class TetrominoJ final : public Tetromino {
  public:
    /**
     * @brief TetrominoJ constructor.
     *
     * @param anchorPoint The TetrominoJ's anchor-point.
     */
    TetrominoJ(Vec2 &&anchorPoint);
};

// #### T Shape ####

/**
 * @class TetrominoT
 */
class TetrominoT final : public Tetromino {
    /**
     * @brief TetrominoT constructor.
     *
     * @param anchorPoint The TetrominoT's anchor-point.
     */
  public:
    TetrominoT(Vec2 &&anchorPoint);
};

#endif
