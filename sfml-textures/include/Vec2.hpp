#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

template <typename T>
struct Vec2 {
  T x{0.0f}, y{0.0f};

  Vec2() = default;
  Vec2(T x, T y) : x(x), y(y) {}
  Vec2(const sf::Vector2<T>& vector) : x(vector.x), y(vector.y) {}

  operator sf::Vector2<T>() const { return sf::Vector2<T>(x, y); }

  bool operator==(const Vec2<T>& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Vec2<T>& rhs) const { return !(*this == rhs); }

  Vec2<T> operator+(const Vec2<T>& rhs) {
    return Vec2<T>(x + rhs.x, y + rhs.y);
  }

  Vec2<T> operator-(const Vec2<T>& rhs) {
    return Vec2<T>(x - rhs.x, y - rhs.y);
  }

  Vec2<T> operator*(T scale) { return Vec2<T>(x * scale, y * scale); }

  Vec2<T> operator/(T scale) {
    if (scale == 0) throw std::runtime_error("Division by zero!\n");
    return Vec2<T>(x / scale, y / scale);
  }

  Vec2<T> operator+=(const Vec2<T>& rhs) {
    *this = *this + rhs;
    return *this;
  }

  Vec2<T> operator-=(const Vec2<T>& rhs) {
    *this = *this - rhs;
    return *this;
  }

  Vec2<T> operator*=(T scale) {
    *this = *this * scale;
    return *this;
  }

  Vec2<T> operator/=(T scale) {
    *this = *this * scale;
    return *this;
  }

  T length() const { return std::sqrt(x * x + y * y); }

  void normalize() {
    float len = length();
    if (len > 0) {
      x /= len;
      y /= len;
    }
  }

  T distance(const Vec2<T>& other) const {
    return std::sqrt((x - other.x) * (x - other.x) +
                     (y - other.y) * (y - other.y));
  }
};