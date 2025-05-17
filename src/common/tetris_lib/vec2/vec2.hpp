/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VEC2_HPP
#define VEC2_HPP

#include <cstddef>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <type_traits>
#include <utility>

class Vec2Test;

/**
 * @class Vec2
 *
 * @brief Represents a 2D vector.
 */
class Vec2 {
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

    ~Vec2() = default;

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

    // #### Structured binding ####

    template <size_t N> decltype(auto) get() const {
        if constexpr (N == 0) {
            return x_;
        } else if constexpr (N == 1) {
            return y_;
        }
    }

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes a Vec2 to json.
     */
    nlohmann::json serialize() const;

    /**
     * @brief Deserializes a Vec2 from json.
     */
    void deserialize(const nlohmann::json &j);

    /* ------------------------------------------------
     *          Test Fixture Class
     * ------------------------------------------------*/

    friend Vec2Test;
};

// #### Structured binding ####

namespace std {
    template <> struct tuple_size<Vec2> : std::integral_constant<size_t, 2> {};

    template <std::size_t N> struct tuple_element<N, Vec2> {
        using type = decltype(std::declval<Vec2>().get<N>());
    };
} // namespace std

#endif // VEC2_HPP
