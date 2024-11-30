#ifndef COORDINATE_HPP
#define COORDINATE_HPP

class Coordinate {
  private:
    int col_;
    int row_;

  public:
    // #### Constructors  ####

    Coordinate(int row, int col);

    Coordinate(const Coordinate &other);

    Coordinate(Coordinate &&other);

    // #### Assignment Operators  ####

    Coordinate &operator=(const Coordinate &other);

    Coordinate &operator=(Coordinate &&other);

    // #### Getters ####

    int getRow() const noexcept;

    int getCol() const noexcept;

    // #### Setters ####

    void setRow(int row);

    void setCol(int col);

    void moveRow(int row);

    void moveCol(int col);

    // #### Operators ####

    bool operator==(const Coordinate &other) const;

    Coordinate operator+(const Coordinate &other) const;

    Coordinate &operator+=(const Coordinate &other);

    Coordinate operator-(const Coordinate &other) const;

    Coordinate &operator-=(const Coordinate &other);

    Coordinate operator-() const;
};

#endif
