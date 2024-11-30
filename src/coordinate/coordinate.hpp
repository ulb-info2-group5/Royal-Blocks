#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>

class Coordinate {
  private:
    int col_;
    int row_;

  public:
    // #### Constructors  ####

    Coordinate(int row, int col);

    Coordinate(const Coordinate &other);

    Coordinate(Coordinate &&other);

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

    // #### Operators ####

    virtual bool operator==(const Coordinate &other) const;

    virtual Coordinate operator+(const Coordinate &other) const;

    virtual Coordinate &operator+=(const Coordinate &other);

    virtual Coordinate operator-(const Coordinate &other) const;

    virtual Coordinate &operator-=(const Coordinate &other);

    virtual Coordinate operator-() const;

    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coord);
};

#endif
