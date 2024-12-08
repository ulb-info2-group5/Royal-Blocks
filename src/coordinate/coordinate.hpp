#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>

class CoordinateTest;

/**
 * @class Coordinate
 *
 * @brief Represents a coordinate with row and column indices in a matrix.
 */
class Coordinate {
  private:
    int col_;
    int row_;

  public:
    // #### Constructors  ####

    /**
     * @brief Coordinate's default constructor, initalizes row and column
     * indices to 0.
     */
    Coordinate();

    /**
     * @brief Coordinate's constructor.
     *
     * @param row The row index
     * @param col The column index
     */
    Coordinate(int row, int col);

    /**
     * @brief Coordinate's copy constructor.
     *
     * @param other The other Coordinate object.
     */
    Coordinate(const Coordinate &other);

    /**
     * @brief Coordinate's move constructor.
     *
     * @param other The other Coordinate object r-value.
     */
    Coordinate(Coordinate &&other);

    // #### Destructor ####

    /**
     * @brief Coordinate's Destructor.
     */
    virtual ~Coordinate();

    // #### Assignment Operators  ####

    /**
     * @brief Coordinate's assignment operator.
     *
     * @param other Another Coordinate to assign from.
     * @return Reference to this Coordinate.
     */
    virtual Coordinate &operator=(const Coordinate &other);

    /**
     * @brief Coordinate's move assignment operator.
     *
     * @param other Another Coordinate to assign from as an r-value.
     * @return Reference to this Coordinate.
     */
    virtual Coordinate &operator=(Coordinate &&other);

    // #### Getters ####

    /**
     * @brief Returns the row index.
     *
     * @return Row index.
     */
    virtual int getRow() const noexcept;

    /**
     * @brief Returns the column index.
     *
     * @return Column index.
     */
    virtual int getCol() const noexcept;

    // #### Setters ####

    /**
     * @brief Sets the row index.
     *
     * @param row Row index.
     */
    virtual void setRow(int row);

    /**
     * @brief Sets the column index.
     *
     * @param col Column index.
     */
    virtual void setCol(int col);

    /**
     * @brief Moves relatively to current row index.
     *
     * @param row Value to add to the current row index.
     */
    virtual void moveRow(int row);

    /**
     * @brief Moves relatively to current column index.
     *
     * @param col Value to add to the current col index.
     */
    virtual void moveCol(int col);

    // #### Comparison Operators ####

    /**
     * @brief Compares two Coordinate objects.
     *
     * @param other The Coordinate to compare with.
     * @return True if the two Tetrominoes are equal; otherwise, false.
     */
    virtual bool operator==(const Coordinate &other) const;

    /**
     * @brief Compares two Coordinate objects.
     *
     * @param other The Coordinate to compare with.
     * @return True if the two Tetrominoes are different; otherwise, false.
     */
    virtual bool operator!=(const Coordinate &other) const;

    // #### Arithmetic Operators ####

    /**
     * @brief Adds two Coordinate objects element-wise.
     *
     * @param other The Coordinate to add.
     * @return A new Coordinate with the sum of the respective row and column
     * indices.
     */
    virtual Coordinate operator+(const Coordinate &other) const;

    /**
     * @brief Adds another Coordinate to this one element-wise.
     *
     * @param other The Coordinate to add.
     * @return Reference to this Coordinate after the addition.
     */
    virtual Coordinate &operator+=(const Coordinate &other);

    /**
     * @brief Subtracts another Coordinate from this one element-wise.
     *
     * @param other The Coordinate to subtract.
     * @return A new Coordinate with the difference of the respective row and
     * column indices.
     */
    virtual Coordinate operator-(const Coordinate &other) const;

    /**
     * @brief Subtracts another Coordinate from this one element-wise.
     *
     * @param other The Coordinate to subtract.
     * @return Reference to this Coordinate after the subtraction.
     */
    virtual Coordinate &operator-=(const Coordinate &other);

    /**
     * @brief Returns a coordinate whith signs of row and column
     * indices flipped.
     *
     * @return A new Coordinate with negated row and column indices.
     */
    virtual Coordinate operator-() const;

    // #### Rotation #####

    /**
     * @brief Rotate this coordinate around the given rotation center in the
     * given direction.
     *
     * @param rotationCenter The rotation center.
     * @param rotateClockwise Whether to rotate clockwise.
     */
    virtual const Coordinate &rotateAround(const Coordinate &rotationCenter,
                                           bool rotateClockwise);

    // #### Output Stream ####

    /**
     * @brief Outputs the Coordinate to a stream.
     *
     * @param os The output stream.
     * @param coord The Coordinate to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coord);

    // #### Test Fixture Class ####

    friend CoordinateTest;
};

#endif
