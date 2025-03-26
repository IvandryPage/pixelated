#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityManager.hpp"

class Game {
 public:
  Game();
  void run();

 private:
  sf::RenderWindow window_;
  sf::Font font_;
  sf::Clock delta_clock_;
  int current_frame_{0};
  EntityManager entity_manager_;
  bool is_paused_{false};
  bool is_running_{true};

  void initialize();
  void eventSystem();
  void updateSystem(float delta_time);
  void renderSystem();

  void spawnPlayer();
  void movePlayer(float delta_time);
  void spawnBall();
  void moveBall(float delta_time);
  void spawnText();
  void updateText();
};