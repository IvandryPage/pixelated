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
  auto e = entity_manager_.addEntity("shape");
  e->add<Transform>(
      Vec2<float>(window_.getSize().x / 2.0f, window_.getSize().y / 2.0f),
      Vec2<float>(100, 200));
  e->add<Shape>(100.0f, 6, sf::Color(255, 255, 255), sf::Color(0, 0, 0), 5.0f);

  while (window_.isOpen()) {
    float delta_time = delta_clock_.restart().asSeconds();
    entity_manager_.update();
    eventSystem();
    updateSystem(delta_time);
    renderSystem();
    current_frame_++;
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

void Game::updateSystem(float delta_time) {
  // all system that changes something goes here
  auto e = entity_manager_.getEntities("shape");
  e.front()->get<Transform>().position +=
      e.front()->get<Transform>().velocity * delta_time;
  e.front()->get<Shape>().circle.setOrigin(
      e.front()->get<Shape>().circle.getGeometricCenter());
  e.front()->get<Transform>().angle = sf::degrees(1.0f);
  e.front()->get<Shape>().circle.rotate(e.front()->get<Transform>().angle);
}

void Game::renderSystem() {
  window_.clear();
  for (auto& e : entity_manager_.getEntities()) {
    if (e->has<Shape>()) {
      e->get<Shape>().circle.setPosition(e->get<Transform>().position);
      window_.draw(e->get<Shape>().circle);
    }
  }
  window_.display();
}