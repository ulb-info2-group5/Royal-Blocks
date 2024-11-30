#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../coordinate/coordinate.hpp"

#include <memory>
#include <vector>

enum class TetrominoShape;

enum class Direction { left, right, down };

class Tetromino {
  private:
    int width_;
    int height_;
    Coordinate anchorPoint_;
    std::vector<Coordinate> body_;

  protected:
    // #### Constructors ####

    Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body);

    Tetromino(const Tetromino &other);

    Tetromino(Tetromino &&other);

    // #### Assignment Operators  ####

    Tetromino &operator=(const Tetromino &other);

    Tetromino &operator=(Tetromino &&other);

  public:
    // #### Factory ####

    static std::unique_ptr<Tetromino> makeTetromino(TetrominoShape shape,
                                                    Coordinate &&anchorPoint);

    // #### Getters ####

    virtual int getWidth() const noexcept;

    virtual int getHeight() const noexcept;

    virtual const std::vector<Coordinate> &getBody() const noexcept;

    // #### Tetromino Actions ####

    virtual void tryRotate();

    virtual void tryMove(Direction direction);

    // #### Debug ####

    virtual void debugPrint() const;
};

#endif
