#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../coordinate/coordinate.hpp"

#include <memory>
#include <vector>

enum class TetrominoShape;

enum class Direction { left, right, down };

class Tetromino {
  private:
    int width_ = 0;
    int height_ = 0;
    Coordinate anchorPoint_;
    std::vector<Coordinate> body_;

  protected:
    // #### Constructor ####

    Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body);

    Tetromino(const Tetromino &other);

    Tetromino(Tetromino &&other);

    // #### Assignment Operators  ####

    Tetromino &operator=(const Tetromino &other);

    Tetromino &operator=(Tetromino &&other);

  public:
    // #### Destructor ####

    virtual ~Tetromino();

    // #### Factory ####

    static std::unique_ptr<Tetromino> makeTetromino(TetrominoShape shape,
                                                    Coordinate &&anchorPoint);

    // #### Getters ####

    virtual int getWidth() const noexcept;

    virtual int getHeight() const noexcept;

    virtual TetrominoShape getShape() const noexcept = 0;

    virtual const Coordinate &getAnchorPoint() const noexcept;

    virtual const std::vector<Coordinate> &getBody() const noexcept;

    // #### Tetromino Actions ####

    virtual void rotate();

    virtual void move(Direction direction);

    // #### Output Stream ####

    friend std::ostream &operator<<(std::ostream &os,
                                    const Tetromino &tetromino);
};

#endif
