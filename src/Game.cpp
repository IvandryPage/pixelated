#include "Game.h"

Game::Game() { initialize(); }

void Game::initialize() {
  window_.create(sf::VideoMode({1920, 1080}), "Game Engine!",
                 sf::State::Fullscreen);
  window_.setFramerateLimit(60);

  if (!font_.openFromFile("assets/ShareTechMono-Regular.ttf")) {
    std::cerr << "Font Load Error: can't open font!";
    exit(EXIT_FAILURE);
  }
}

void Game::run() {
  while (window_.isOpen()) {
  }
}

void Game::eventSystem() {
  while (std::optional<sf::Event> event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_.close();
    }

    if (event->is<sf::Event::KeyPressed>()) {
      switch (event->getIf<sf::Event::KeyPressed>()->scancode) {
        case sf::Keyboard::Scan::Escape:
          window_.close();
          break;
        default:
          break;
      }
    }
  }
}

void Game::updateSystem(float delta_time) {}

void Game::renderSystem() {
  window_.clear();
  window_.display();
}