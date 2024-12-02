#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>

class Coordinate {
  private:
    int col_ = 0;
    int row_ = 0;

  public:
    // #### Constructors  ####

    Coordinate();

    Coordinate(int row, int col);

    Coordinate(const Coordinate &other);

    Coordinate(Coordinate &&other);

    static Coordinate fromCartesian(int x, int y);

    // #### Destructor ####

    virtual ~Coordinate();

    // #### Assignment Operators  ####

    virtual Coordinate &operator=(const Coordinate &other);

    virtual Coordinate &operator=(Coordinate &&other);

    // #### Getters ####

    virtual int getRow() const noexcept;

    virtual int getCol() const noexcept;

    // #### Setters ####

    virtual void setRow(int row);

    virtual void setCol(int col);

    virtual void moveRow(int row);

    virtual void moveCol(int col);

    // #### Comparison Operators ####

    virtual bool operator==(const Coordinate &other) const;

    virtual bool operator!=(const Coordinate &other) const;

    // #### Arithmetic Operators ####

    virtual Coordinate operator+(const Coordinate &other) const;

    virtual Coordinate &operator+=(const Coordinate &other);

    virtual Coordinate operator-(const Coordinate &other) const;

    virtual Coordinate &operator-=(const Coordinate &other);
    virtual Coordinate operator-() const;

    // #### Rotation #####

    virtual const Coordinate &rotateAround(const Coordinate &rotationCenter,
                                           bool rotateClockwise);

    // #### Output Stream ####

    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coord);
};

#endif
