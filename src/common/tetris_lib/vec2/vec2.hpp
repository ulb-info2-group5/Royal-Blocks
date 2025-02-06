#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>

class Vec2Test;

/**
 * @class Vec2
 *
 * @brief Represents a 2D vector.
 */
class Vec2 final {
  private:
    int x_;
    int y_;

  public:
    // #### Constructors ####

    /**
     * @brief Constructor.
     *
     * @param x The x component
     * @param y The y component
     */
    Vec2(int x = 0, int y = 0);

    Vec2(const Vec2 &) = default;
    Vec2(Vec2 &&) = default;

    // #### Assignment ####

    Vec2 &operator=(const Vec2 &) = default;
    Vec2 &operator=(Vec2 &&) = default;

    // #### Destructor ####

    virtual ~Vec2() = default;

    // #### Getters ####

    /**
     * @brief Returns the X component.
     *
     * @return X component.
     */
    int getX() const noexcept;

    /**
     * @brief Returns the Y component.
     *
     * @return Y component.
     */
    int getY() const noexcept;

    // #### Setters ####

    /**
     * @brief Sets the X index.
     *
     * @param x X component.
     */
    void setX(int x);

    /**
     * @brief Sets the Y index.
     *
     * @param y Y component.
     */
    void setY(int y);

    /**
     * @brief Moves relatively on the x-axis.
     *
     * @param x Value to add to the current x-axis position.
     */
    void moveX(int x);

    /**
     * @brief Moves relatively on the y-axis.
     *
     * @param y Value to add to the current y-axis position.
     */
    void moveY(int y);

    // #### Comparison Operators ####

    /**
     * @brief Compares two Vec2 objects.
     *
     * @param other The Vec2 to compare with.
     * @return True if the two Vec2's are equal; otherwise, false.
     */
    bool operator==(const Vec2 &other) const;

    /**
     * @brief Compares two Vec2 objects.
     *
     * @param other The Vec2 to compare with.
     * @return True if the two Vec2's are different; otherwise, false.
     */
    bool operator!=(const Vec2 &other) const;

    // #### Arithmetic Operators ####

    /**
     * @brief Adds two Vec2 objects component-wise.
     *
     * @param other The Vec2 to add.
     * @return A new Vec2 with the sum of the respective x and y components.
     */
    Vec2 operator+(const Vec2 &other) const;

    /**
     * @brief Adds another Vec2 to this one component-wise.
     *
     * @param other The Vec2 to add.
     * @return Reference to this Vec2.
     */
    Vec2 &operator+=(const Vec2 &other);

    /**
     * @brief Subtracts another Vec2 from this one element-wise.
     *
     * @param other The Vec2 to subtract.
     * @return A new Vec2 with the difference of the respective x and y
     * components.
     */
    Vec2 operator-(const Vec2 &other) const;

    /**
     * @brief Subtracts another Vec2 from this one component-wise.
     *
     * @param other The Vec2 to subtract.
     * @return Reference to this Vec2.
     */
    Vec2 &operator-=(const Vec2 &other);

    /**
     * @brief Returns a vec2 whith x and y components negated.
     *
     * @return A new Vec2 with negated row and column indices.
     */
    Vec2 operator-() const;

    // #### Rotation #####

    /**
     * @brief Rotate this Vec2 around the given rotation center Vec2 in the
     * given direction.
     *
     * @param rotationCenter The rotation center.
     * @param rotateClockwise True to rotate clockwise, false otherwise.
     */
    const Vec2 &rotateAround(const Vec2 &rotationCenter, bool rotateClockwise);

    // #### Output Stream ####

    /**
     * @brief Outputs the Vec2 to a stream.
     *
     * @param os The output stream.
     * @param Vec2 The Vec2 to output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Vec2 &vec2);

    // #### Test Fixture Class ####

    friend Vec2Test;
};

#endif // VEC2_HPP
