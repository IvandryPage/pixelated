#pragma once
#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

struct Component {
  bool exists{false};
};

struct Shape : public Component {
  sf::CircleShape circle;
  Shape() = default;

  Shape(float radius, size_t points, sf::Color fill, sf::Color outline,
        float thickness)
      : circle(radius, points) {
    circle.setFillColor(fill);
    circle.setOutlineColor(outline);
    circle.setOutlineThickness(thickness);
    circle.setOrigin(Vec2<float>(radius, radius));
  }
};

struct Transform : public Component {
  Vec2<float> position{0, 0};
  Vec2<float> velocity{0, 0};
  sf::Angle angle;

  Transform() = default;
  Transform(const Vec2<float>& position, const Vec2<float>& velocity)
      : position(position), velocity(velocity) {}
};

struct Collision : public Component {
  float radius;
  Collision() = default;
  Collision(float radius) : radius(radius) {}
};

struct Input : public Component {
  bool up{false};
  bool down{false};
  bool left{false};
  bool right{false};
  bool shoot{false};

  Input() = default;
};

struct LifeSpan : public Component {
  int total{0};
  int remaining{0};
  LifeSpan() = default;
  LifeSpan(int total_life_span)
      : total(total_life_span), remaining(total_life_span) {}
};

struct Score : public Component {
  int score{0};

  Score() = default;
  Score(int score) : score(score) {}
};