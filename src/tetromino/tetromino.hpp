#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../coordinate/coordinate.hpp"
#include "rotation_index/rotation_index.hpp"

#include <cstdint>
#include <memory>
#include <vector>

enum class TetrominoShape;

enum class Direction { left, right, down };

class Tetromino {
  private:
    int width_ = 0;
    int height_ = 0;
    TetrominoShape shape_;
    Coordinate anchorPoint_;
    std::vector<Coordinate> body_;

    // SRS-related
    RotationIndex rotationIdx_;
    RotationIndex oldRotationIdx_;
    const std::vector<std::vector<Coordinate>> &offsetData_;

  protected:
    // #### Kick Data Constants ####

    static const std::vector<std::vector<Coordinate>> O_OFFSET_DATA;
    static const std::vector<std::vector<Coordinate>> I_OFFSET_DATA;
    static const std::vector<std::vector<Coordinate>> ZLSJT_OFFSET_DATA;

    // #### Constructor ####

    Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body,
              const std::vector<std::vector<Coordinate>> &kickData,
              TetrominoShape shape);

    Tetromino(Tetromino &&other);

    // #### Assignment Operators  ####

    // Tetromino &operator=(const Tetromino &other);
    // Tetromino &operator=(Tetromino &&other);

  public:
    // #### Constructor ####
    Tetromino(const Tetromino &other);

    // #### Destructor ####

    virtual ~Tetromino();

    // #### Factory ####

    static std::unique_ptr<Tetromino> makeTetromino(TetrominoShape shape,
                                                    Coordinate &&anchorPoint);

    // #### Getters ####

    virtual int getWidth() const noexcept;

    virtual int getHeight() const noexcept;

    virtual TetrominoShape getShape() const noexcept;

    virtual const Coordinate &getAnchorPoint() const noexcept;

    virtual const std::vector<Coordinate> &getBody() const noexcept;

    // TODO: define this method
    virtual std::unique_ptr<Tetromino>
    getNthKick(uint8_t kickIndex) const noexcept;

    // #### Tetromino Actions ####

    virtual void rotate(bool rotateClockwise);

    virtual void move(Direction direction);

    // #### Output Stream ####

    friend std::ostream &operator<<(std::ostream &os,
                                    const Tetromino &tetromino);
};

#endif
