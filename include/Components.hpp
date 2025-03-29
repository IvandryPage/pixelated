#pragma once
#include <SFML/Graphics.hpp>

#include "Vec2.hpp"

struct Component {
  bool exists{false};
};

struct TransformComponent : public Component {
  Vec2<float> position{0.0f, 0.0f};
  Vec2<float> scale{1.0f, 1.0f};
  constexpr static sf::Angle default_rotation{sf::degrees(0.0f)};
  sf::Angle rotation;

  TransformComponent() = default;
  explicit TransformComponent(const Vec2<float>& position,
                              std::optional<sf::Angle> rotation = std::nullopt,
                              std::optional<Vec2<float>> scale = std::nullopt)
      : position(position),
        rotation(rotation.value_or(sf::degrees(0.0f))),
        scale(scale.value_or(Vec2<float>(1.0f, 1.0f))) {}
};

struct VelocityComponent : public Component {
  Vec2<float> velocity{0.0f, 0.0f};
  float acceleration{0.0f};

  VelocityComponent() = default;
  explicit VelocityComponent(const Vec2<float>& velocity,
                             std::optional<float> acceleration)
      : velocity(velocity), acceleration(acceleration.value_or(0.0f)) {}
};

struct SpriteComponent : public Component {
  std::optional<sf::Sprite> sprite;
  Vec2<float> size{0.0f, 0.0f};
  bool is_visible{true};

  SpriteComponent() = default;
  explicit SpriteComponent(sf::Texture* texture, const Vec2<float>& size)
      : size(size) {
    if (!texture) {
      std::cerr << "SpriteComponent received a null texture!\n";
    } else {
      sprite = sf::Sprite(*texture);
    }
  }
};

struct AnimationComponent : public Component {
  std::string name;
  int frame_count{0};
  int current_frame{0};
  int frame_speed{0};
  bool is_looping{false};

  AnimationComponent() = default;
  explicit AnimationComponent(const std::string& name, int frame_count,
                              int frame_speed, bool looping)
      : name(name),
        frame_count(frame_count),
        frame_speed(frame_speed),
        is_looping(looping) {}
};

struct BoundingBoxComponent : public Component {
  sf::FloatRect bounds{Vec2<float>(0.0f, 0.0f), Vec2<float>(0.0f, 0.0f)};

  BoundingBoxComponent() = default;
  explicit BoundingBoxComponent(const sf::FloatRect& bounds) : bounds(bounds) {}
};

struct RectColliderComponent : public Component {
  Vec2<float> size{0.0f, 0.0f};
  Vec2<float> half_size{0.0f, 0.0f};

  RectColliderComponent() = default;
  explicit RectColliderComponent(const Vec2<float>& size)
      : size(size), half_size(size.x / 2.0f, size.y / 2.0f) {}
};

struct CircleColliderComponent : public Component {
  float radius{0.0f};

  CircleColliderComponent() = default;
  explicit CircleColliderComponent(float radius) : radius(radius) {}
};

struct InputComponent : public Component {
  bool up{false};
  bool down{false};
  bool left{false};
  bool right{false};

  InputComponent() = default;
};

struct LifeSpanComponent : public Component {
  int total{0};
  int remaining{0};

  LifeSpanComponent() = default;
  LifeSpanComponent(int total_life_span)
      : total(total_life_span), remaining(total_life_span) {}
};

struct CircleShapeComponent : public Component {
  sf::CircleShape shape;

  CircleShapeComponent() = default;
  CircleShapeComponent(float radius, size_t points, sf::Color fill,
                       sf::Color outline, float thickness)
      : shape(radius, points) {
    shape.setFillColor(fill);
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setOrigin(Vec2<float>(radius, radius));
  }
};

struct RectangleShapeComponent : public Component {
  sf::RectangleShape shape;

  RectangleShapeComponent() = default;
  RectangleShapeComponent(const Vec2<float>& size, const sf::Color& fill,
                          const sf::Color& outline, float thickness)
      : shape(size) {
    shape.setFillColor(fill);
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setOrigin(shape.getGeometricCenter());
  }
};