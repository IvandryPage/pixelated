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
  spawnText();
  while (window_.isOpen()) {
    srand(time(0));
    float delta_time = delta_clock_.restart().asSeconds();
    if (current_frame_ % 180 == 0) {
      spawnBall();
    }
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
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().up = true;
            }
          }
          break;
        case sf::Keyboard::Scan::S:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().down = true;
            }
          }
          break;
        case sf::Keyboard::Scan::A:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().left = true;
            }
          }
          break;
        case sf::Keyboard::Scan::D:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().right = true;
            }
          }
          break;
        case sf::Keyboard::Scan::Up:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().up = true;
            }
          }
          break;
        case sf::Keyboard::Scan::Down:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().down = true;
            }
          }
          break;
        case sf::Keyboard::Scan::Left:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().left = true;
            }
          }
          break;
        case sf::Keyboard::Scan::Right:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().right = true;
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
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().up = false;
            }
          }
          break;
        case sf::Keyboard::Scan::S:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().down = false;
            }
          }
          break;
        case sf::Keyboard::Scan::A:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().left = false;
            }
          }
          break;
        case sf::Keyboard::Scan::D:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 0) {
              e->get<Input>().right = false;
            }
          }
          break;
        case sf::Keyboard::Scan::Up:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().up = false;
            }
          }
          break;
        case sf::Keyboard::Scan::Down:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().down = false;
            }
          }
          break;
        case sf::Keyboard::Scan::Left:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().left = false;
            }
          }
          break;
        case sf::Keyboard::Scan::Right:
          for (auto& e : entity_manager_.getEntities("player")) {
            if (e->has<Input>() && e->id() == 1) {
              e->get<Input>().right = false;
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
  moveBall(delta_time);
  updateText();
}

void Game::renderSystem() {
  window_.clear();
  for (auto& e : entity_manager_.getEntities()) {
    if (e->has<Shape>()) {
      e->get<Shape>().circle.setPosition(e->get<Transform>().position);
      e->get<Shape>().circle.rotate(e->get<Transform>().angle);
      window_.draw(e->get<Shape>().circle);
    }

    if (e->has<TextDraw>()) {
      e->get<TextDraw>().text->setPosition(e->get<Transform>().position);
      window_.draw(*(e->get<TextDraw>().text));
    }
  }
  window_.display();
}

void Game::spawnPlayer() {
  auto player1 = entity_manager_.addEntity("player");
  player1->add<Input>();
  player1->add<Transform>(Vec2<float>(100.0f, window_.getSize().y / 2.0f),
                          Vec2<float>(800.0f, 800.0f));
  player1->add<Shape>(50.0f, rand() % 8 + 3, sf::Color::Blue, sf::Color::White,
                      2.0f);
  player1->add<Collision>(50.0f);
  player1->add<Score>();
  player1->get<Shape>().circle.setOrigin(
      player1->get<Shape>().circle.getGeometricCenter());
  player1->get<Transform>().angle = sf::degrees(6.0f);

  auto player2 = entity_manager_.addEntity("player");
  player2->add<Input>();
  player2->add<Transform>(
      Vec2<float>(window_.getSize().x - 100.0f, window_.getSize().y / 2.0f),
      Vec2<float>(800.0f, 800.0f));
  player2->add<Shape>(50.0f, rand() % 3 + 4, sf::Color::Red, sf::Color::White,
                      2.0f);
  player2->add<Collision>(50.0f);
  player2->add<Score>();
  player2->get<Shape>().circle.setOrigin(
      player2->get<Shape>().circle.getGeometricCenter());
  player2->get<Transform>().angle = sf::degrees(-6.0f);
}

void Game::movePlayer(float delta_time) {
  for (auto e : entity_manager_.getEntities()) {
    if (!e->has<Input>()) {
      continue;
    }

    float left_border = (e->id()) ? window_.getSize().x - 500.0f : 0;
    float right_border = (e->id()) ? window_.getSize().x : 400.0f;

    if (e->get<Input>().up && e->get<Transform>().position.y >= 100) {
      e->get<Transform>().position.y -=
          e->get<Transform>().velocity.y * delta_time;
    }
    if (e->get<Input>().down &&
        e->get<Transform>().position.y <= window_.getSize().y - 100) {
      e->get<Transform>().position.y +=
          e->get<Transform>().velocity.y * delta_time;
    }
    if (e->get<Input>().left && e->get<Transform>().position.x >= left_border) {
      e->get<Transform>().position.x -=
          e->get<Transform>().velocity.x * delta_time;
      e->get<Transform>().angle = sf::degrees(-3.0f);
    }
    if (e->get<Input>().right &&
        e->get<Transform>().position.x <= right_border) {
      e->get<Transform>().position.x +=
          e->get<Transform>().velocity.x * delta_time;
      e->get<Transform>().angle = sf::degrees(3.0f);
    }
  }
}

void Game::spawnBall() {
  auto ball = entity_manager_.addEntity("ball");
  float speed = 450.0f;
  float angle = (rand() % 360) * (M_PI / 180.0f);
  Vec2<float> random_velocity(std::cos(angle) * speed, std::sin(angle) * speed);
  ball->add<Transform>(
      Vec2<float>(window_.getSize().x / 2.0f, window_.getSize().y / 2.0f),
      random_velocity);
  ball->add<Shape>(20.0f, rand() % 30 + 3, sf::Color::White, sf::Color::White,
                   1.0f);
  ball->add<Collision>(22.0f);
  ball->add<LifeSpan>();
  ball->get<Shape>().circle.setOrigin(
      ball->get<Shape>().circle.getGeometricCenter());
  ball->get<Transform>().angle = sf::degrees(3.0f);
}

void Game::moveBall(float delta_time) {
  auto balls = entity_manager_.getEntities("ball");
  auto players = entity_manager_.getEntities("player");
  for (auto& ball : balls) {
    if (current_frame_ % 350 == 0) {
      ball->get<Transform>().velocity.x *= 1.5f;
    }
    ball->get<Transform>().position +=
        ball->get<Transform>().velocity * delta_time;

    for (auto& player : players) {
      if ((ball->get<Collision>().radius + player->get<Collision>().radius) >=
          ball->get<Transform>().position.distance(
              player->get<Transform>().position)) {
        Vec2 collision_normal =
            ball->get<Transform>().position - player->get<Transform>().position;
        collision_normal.normalize();

        Vec2<float> product =
            ball->get<Transform>().velocity * collision_normal;

        ball->get<Transform>().velocity =
            ball->get<Transform>().velocity -
            collision_normal * (2.0f * (product.x + product.y));

        ball->get<Transform>().position +=
            collision_normal * ball->get<Collision>().radius;

        if (ball->get<Transform>().velocity.x <= 0) {
          ball->get<Transform>().angle = sf::degrees(-3.0f);
        }
      }
    }

    if (ball->get<Collision>().radius + ball->get<Transform>().position.y >=
            window_.getSize().y - 100.0f ||
        ball->get<Transform>().position.y - ball->get<Collision>().radius <=
            100.0f) {
      ball->get<Transform>().velocity.y *= -1.0f;
    }

    if (ball->get<Collision>().radius + ball->get<Transform>().position.x >=
        window_.getSize().x) {
      for (auto e : entity_manager_.getEntities("player")) {
        if (e->id() == 0) {
          e->get<Score>().score++;
        }
      }
      ball->destroy();
    }
    if (ball->get<Transform>().position.x - ball->get<Collision>().radius <=
        0) {
      for (auto e : entity_manager_.getEntities("player")) {
        if (e->id() == 1) {
          e->get<Score>().score++;
        }
      }
      ball->destroy();
    }
  }
}

void Game::spawnText() {
  auto e = entity_manager_.addEntity("text");
  e->add<Transform>();
  e->add<TextDraw>(font_, "Player 1 : 0", 36);

  auto e2 = entity_manager_.addEntity("text");
  e2->add<Transform>();
  e2->add<TextDraw>(font_, "Player 2 : 0", 36);
  e2->get<Transform>().position.x = window_.getSize().x - 240;
}

void Game::updateText() {
  auto t = entity_manager_.getEntities("text");
  auto p = entity_manager_.getEntities("player");
  t.front()->get<TextDraw>().text->setString(
      "Player 1: " + std::to_string(p.front()->get<Score>().score));
  t.back()->get<TextDraw>().text->setString(
      "Player 2: " + std::to_string(p.back()->get<Score>().score));
}