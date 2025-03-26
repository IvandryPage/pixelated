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
  spawnPlayer();
  // spawnBall();
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
        case sf::Keyboard::Scan::W:
          for (auto e : entity_manager_.getEntities("player")) {
            if (e->has<Input>()) {
              e->get<Input>().up = true;
            }
          }
          break;
        case sf::Keyboard::Scan::S:
          for (auto e : entity_manager_.getEntities("player")) {
            if (e->has<Input>()) {
              e->get<Input>().down = true;
            }
          }
          break;
        default:
          break;
      }
    }

    if (event->is<sf::Event::KeyReleased>()) {
      switch (event->getIf<sf::Event::KeyReleased>()->scancode) {
        case sf::Keyboard::Scan::W:
          for (auto e : entity_manager_.getEntities("player")) {
            if (e->has<Input>()) {
              e->get<Input>().up = false;
            }
          }
          break;
        case sf::Keyboard::Scan::S:
          for (auto e : entity_manager_.getEntities("player")) {
            if (e->has<Input>()) {
              e->get<Input>().down = false;
            }
          }
          break;
        default:
          break;
      }
    }
  }
}

void Game::updateSystem(float delta_time) {
  movePlayer(delta_time);
  // updateScore();
}

void Game::renderSystem() {
  window_.clear();
  for (auto e : entity_manager_.getEntities()) {
    if (e->has<Shape>()) {
      e->get<Shape>().circle.setPosition(e->get<Transform>().position);
      window_.draw(e->get<Shape>().circle);
    }
  }
  window_.display();
}

void Game::spawnPlayer() {
  auto e = entity_manager_.addEntity("player");
  e->add<Input>();
  e->add<Transform>(Vec2<float>(100.0f, window_.getSize().y / 2.0f),
                    Vec2<float>(0, 10.0f));
  e->add<Shape>(50.0f, 8, sf::Color::Red, sf::Color::White, 2.0f);
  e->add<Collision>(50.0f);
  e->add<Score>();

  e->get<Shape>().circle.setOrigin(e->get<Shape>().circle.getGeometricCenter());
}

void Game::movePlayer(float delta_time) {
  for (auto e : entity_manager_.getEntities()) {
    if (!e->has<Input>()) {
      continue;
    }

    if (e->get<Input>().up && e->get<Transform>().position.y >= 100) {
      e->get<Transform>().position -= e->get<Transform>().velocity;
    }
    if (e->get<Input>().down &&
        e->get<Transform>().position.y <= window_.getSize().y - 100) {
      e->get<Transform>().position += e->get<Transform>().velocity;
    }
  }
}