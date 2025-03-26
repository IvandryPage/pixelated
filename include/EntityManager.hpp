#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "Entity.hpp"

class EntityManager {
 public:
  using EntityVec = std::vector<std::shared_ptr<Entity>>;
  using EntityMap = std::map<std::string, EntityVec>;

  EntityManager() = default;
  EntityVec& getEntities() { return entities_; }
  EntityVec& getEntities(const std::string& tag) { return entities_map_[tag]; }

  std::shared_ptr<Entity> addEntity(const std::string& tag) {
    auto e = std::shared_ptr<Entity>(new Entity(tag, total_entities_++));
    entities_to_add_.push_back(e);
    return e;
  }

  void update() {
    for (auto e : entities_to_add_) {
      entities_.push_back(e);
      entities_map_[e->tag()].push_back(e);
    }
    entities_to_add_.clear();

    removeDeadEntities();
  }

  size_t totalEntities() { return total_entities_; }

 private:
  EntityVec entities_;
  EntityVec entities_to_add_;
  EntityMap entities_map_;
  size_t total_entities_{0};

  void removeDeadEntities() {
    entities_.erase(
        std::remove_if(entities_.begin(), entities_.end(),
                       [](const std::shared_ptr<Entity>& e) -> bool {
                         return !e->isAlive();
                       }),
        entities_.end());

    for (auto& [tag, entity_vec] : entities_map_) {
      entity_vec.erase(
          std::remove_if(entity_vec.begin(), entity_vec.end(),
                         [](const std::shared_ptr<Entity>& e) -> bool {
                           return !e->isAlive();
                         }),
          entity_vec.end());
    }
  }
};