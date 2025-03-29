#pragma once

#include <iostream>
#include <tuple>

#include "Components.hpp"
#include "EntityManager.hpp"

class Entity {
 public:
  template <typename TComponent>
  TComponent& get() {
    return std::get<TComponent>(components_);
  }

  template <typename TComponent>
  const TComponent& get() const {
    return std::get<TComponent>(components_);
  }

  template <typename TComponent>
  bool has() const {
    return get<TComponent>().exists;
  }

  template <typename TComponent>
  void remove() {
    get<TComponent>() = TComponent();
  }

  template <typename TComponent, typename... TArgs>
  TComponent& add(TArgs&&... args) {
    auto& component = get<TComponent>();
    component = TComponent(std::forward<TArgs>(args)...);
    component.exists = true;
    return component;
  }

  size_t id() const { return id_; }
  bool isAlive() const { return is_alive_; }
  const std::string& tag() const { return tag_; }

  void destroy() { is_alive_ = false; }

 private:
  using ComponentTuple =
      std::tuple<TransformComponent, VelocityComponent, SpriteComponent,
                 AnimationComponent, BoundingBoxComponent,
                 RectColliderComponent, CircleColliderComponent, InputComponent,
                 LifeSpanComponent, CircleShapeComponent,
                 RectangleShapeComponent>;
  ComponentTuple components_;
  size_t id_{0};
  bool is_alive_{true};
  std::string tag_{"default"};

  Entity() = default;
  Entity(const std::string& tag, size_t id) : id_(id), tag_(tag) {}

  friend class EntityManager;
};