#include "vec2.hpp"

#include <map>
#include <nlohmann/detail/json_ref.hpp>
#include <nlohmann/json.hpp>

/*--------------------------------------------------
                    PUBLIC
--------------------------------------------------*/

// #### Constructor  ####

Vec2::Vec2(int x, int y) : x_{x}, y_{y} {}

// #### Getters ####

int Vec2::getX() const noexcept { return x_; }

int Vec2::getY() const noexcept { return y_; }

// #### Setters ####

void Vec2::setX(int x) { x_ = x; }

void Vec2::setY(int y) { y_ = y; }

void Vec2::moveX(int x) { setX(getX() + x); }

void Vec2::moveY(int y) { setY(getY() + y); }

// #### Comparison Operators ####

bool Vec2::operator==(const Vec2 &other) const {
    return getX() == other.getX() and getY() == other.getY();
}

bool Vec2::operator!=(const Vec2 &other) const { return !(operator==(other)); }

// #### Arithmetic Operators ####

Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2{getX(), getY()} += other;
}

Vec2 &Vec2::operator+=(const Vec2 &other) {
    moveX(other.getX());
    moveY(other.getY());
    return *this;
}

Vec2 Vec2::operator-(const Vec2 &other) const {
    return Vec2{getX(), getY()} -= other;
}

Vec2 &Vec2::operator-=(const Vec2 &other) {
    moveX(-other.getX());
    moveY(-other.getY());
    return *this;
}

Vec2 Vec2::operator-() const { return Vec2{-getX(), -getY()}; }

// #### Rotation #####

const Vec2 &Vec2::rotateAround(const Vec2 &rotationCenter,
                               bool rotateClockwise) {
    // Translate the vec2 relative to the rotation center
    int relativeX = getX() - rotationCenter.getX();
    int relativeY = getY() - rotationCenter.getY();

    // Actual rotation
    int rotatedY = rotateClockwise ? -relativeX : relativeX;
    int rotatedX = rotateClockwise ? relativeY : -relativeY;

    // Translate back to the original vec2 space
    setY(rotatedY + rotationCenter.getY());
    setX(rotatedX + rotationCenter.getX());

    return *this;
}

// #### Output Stream ####

std::ostream &operator<<(std::ostream &os, const Vec2 &vec) {
    os << "(" << vec.getX() << ", " << vec.getY() << ")";
    return os;
}

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json Vec2::serialize() const {
    return nlohmann::json{{"x", x_}, {"y", y_}};
}

void Vec2::deserialize(const nlohmann::json &j) {
    j.at("x").get_to(this->x_);
    j.at("y").get_to(this->y_);
}
