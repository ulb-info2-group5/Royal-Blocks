#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "../coordinate/coordinate.hpp"
#include "rotation_index/rotation_index.hpp"

#include <cstdint>
#include <memory>
#include <vector>

class TetrominoTest;

enum class TetrominoShape;

enum class Direction { Left, Right, Down };

class Tetromino {
  private:
    int width_ = 0;
    int height_ = 0;
    TetrominoShape shape_;
    Coordinate anchorPoint_;
    std::vector<Coordinate> body_;

    // SRS-related
    RotationIndex rotationIdx_;
    RotationIndex prevRotationIdx_;
    const std::vector<std::vector<Coordinate>> &offsetData_;

  protected:
    // #### Kick Data Constants ####

    static const std::vector<std::vector<Coordinate>> O_OFFSET_DATA;
    static const std::vector<std::vector<Coordinate>> I_OFFSET_DATA;
    static const std::vector<std::vector<Coordinate>> ZLSJT_OFFSET_DATA;

    // #### Constructor ####

    Tetromino(Coordinate &&anchorPoint, std::vector<Coordinate> &&body,
              const std::vector<std::vector<Coordinate>> &offsetData,
              TetrominoShape shape);

    Tetromino(Tetromino &&other);

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

    virtual const RotationIndex &getRotationIndex() const noexcept;

    virtual const RotationIndex &getPrevRotationIndex() const noexcept;

    virtual uint8_t getNumOfTests() const noexcept;

    virtual std::unique_ptr<Tetromino>
    getNthKick(uint8_t kickIndex) const noexcept;

    virtual unsigned getColorId() const noexcept;

    // #### Setters ####

    virtual void setAnchorPoint(const Coordinate &anchorPoint);

    // #### Tetromino Actions ####

    virtual void rotate(bool rotateClockwise);

    virtual void move(Direction direction, bool reverse = false);

    // #### Comparisons Operator ####
    virtual bool operator==(const Tetromino &other) const;

    // #### Output Stream ####

    friend std::ostream &operator<<(std::ostream &os,
                                    const Tetromino &tetromino);

    friend TetrominoTest;
};

#endif
