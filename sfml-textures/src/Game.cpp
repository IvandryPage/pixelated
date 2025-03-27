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
  spawnEntities();
  spawnPlayer();
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
      auto key = event->getIf<sf::Event::KeyPressed>()->scancode;
      if (key == sf::Keyboard::Scan::Escape) window_.close();

      for (auto& e : entity_manager_.getEntities("player")) {
        if (key == sf::Keyboard::Scan::A) e->get<Input>().left = true;
        if (key == sf::Keyboard::Scan::D) e->get<Input>().right = true;
        if (key == sf::Keyboard::Scan::W) e->get<Input>().up = true;
        if (key == sf::Keyboard::Scan::S) e->get<Input>().down = true;
      }
    }

    if (event->is<sf::Event::KeyReleased>()) {
      auto key = event->getIf<sf::Event::KeyReleased>()->scancode;

      for (auto& e : entity_manager_.getEntities("player")) {
        if (key == sf::Keyboard::Scan::A) e->get<Input>().left = false;
        if (key == sf::Keyboard::Scan::D) e->get<Input>().right = false;
        if (key == sf::Keyboard::Scan::W) e->get<Input>().up = false;
        if (key == sf::Keyboard::Scan::S) e->get<Input>().down = false;
      }
    }
  }
}

void Game::updateSystem(float delta_time) {
  for (auto& e : entity_manager_.getEntities("player")) {
    auto& input = e->get<Input>();
    if (input.left) {
      e->get<Transform>().position.x -=
          e->get<Transform>().velocity.x * delta_time;
    }
    if (input.right) {
      e->get<Transform>().position.x +=
          e->get<Transform>().velocity.x * delta_time;
    }
    if (input.up) {
      e->get<Transform>().position.y -=
          e->get<Transform>().velocity.y * delta_time;
    }
    if (input.down) {
      e->get<Transform>().position.y +=
          e->get<Transform>().velocity.y * delta_time;
    }
  }

  for (auto& e : entity_manager_.getEntities("object")) {
    for (auto& p : entity_manager_.getEntities("player")) {
      std::cout << "Check for collisions!\n";
      std::cout << "object : p" << e->get<Transform>().position.x << " "
                << e->get<Transform>().position.y << " c"
                << e->get<Collision>().half_size.x << " "
                << e->get<Collision>().half_size.x << '\n';
      std::cout << "player : p" << p->get<Transform>().position.x << " "
                << p->get<Transform>().position.y << " c"
                << p->get<Collision>().half_size.x << " "
                << p->get<Collision>().half_size.x << '\n';
      float dx =
          e->get<Transform>().position.x - p->get<Transform>().position.x;
      float ox = e->get<Collision>().half_size.x +
                 p->get<Collision>().half_size.x - std::abs(dx);
      float dy =
          e->get<Transform>().position.y - p->get<Transform>().position.y;
      float oy = e->get<Collision>().half_size.x +
                 p->get<Collision>().half_size.x - std::abs(dy);

      if (ox > 0 && oy > 0) {
        std::cout << "COLLIDE AT  : " << dx << " " << dy << "\n\n";

        if (ox < oy) {
          if (dx > 0) {
            std::cout << "COLLISION FROM LEFT\n";
            p->get<Transform>().position.x -= ox;
          } else {
            std::cout << "COLLISION FROM RIGHT\n";
            p->get<Transform>().position.x += ox;
          }
        } else {
          if (dy > 0) {
            std::cout << "COLLISION FROM TOP\n";
            p->get<Transform>().position.y -= oy;
          } else {
            std::cout << "COLLISION FROM BOTTOM\n";
            p->get<Transform>().position.y += oy;
          }
        }

        p->get<Collision>().overlap = Vec2<float>(ox, oy);
      }
    }
  }
}

void Game::renderSystem() {
  window_.clear();
  for (auto& e : entity_manager_.getEntities()) {
    if (e->has<Shape>()) {
      e->get<Shape>().rectangle.setPosition(e->get<Transform>().position);
      window_.draw(e->get<Shape>().rectangle);
    }
  }
  window_.display();
}

void Game::spawnPlayer() {
  auto e = entity_manager_.addEntity("player");
  e->add<Transform>(Vec2<float>(250, window_.getSize().y / 2),
                    Vec2<float>(250, 250));
  e->add<Shape>(Vec2<float>(200, 200), sf::Color::Blue);
  e->add<Collision>(Vec2<float>(210, 210));
  e->add<Input>();
  e->get<Shape>().rectangle.setOrigin(
      e->get<Shape>().rectangle.getGeometricCenter());
}

void Game::spawnEntities() {
  auto e = entity_manager_.addEntity("object");
  e->add<Transform>(
      Vec2<float>(window_.getSize().x / 2, window_.getSize().y / 2),
      Vec2<float>(0, 0));
  e->add<Shape>(Vec2<float>(300, 300), sf::Color::Cyan);
  e->add<Collision>(Vec2<float>(310, 310));
  e->get<Shape>().rectangle.setOrigin(
      e->get<Shape>().rectangle.getGeometricCenter());
}