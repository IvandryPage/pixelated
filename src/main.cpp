#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

constexpr float kGravity = 980.0f;
constexpr float kGroundLevel = 500.0f;
std::array<float, 3> HeightLevel{400.0f, 250.0f, 100.0f};
size_t current_level{0};

sf::RenderWindow window;
sf::RectangleShape player;
sf::RectangleShape ground;
std::list<sf::CircleShape> obstacles;
std::array<int, 2> used_height;
sf::Clock game_clock;
float delta_time{0.0f};
float spawn_time{2.0f};
float speed_up_cooldown{10.0f};
int speed_level{0};
float obstacle_speed{-300.0f};

void initialize();
void events();
void update();
void render();
void generateObstacle();
sf::RectangleShape initializePlayer();
sf::RectangleShape initializeGround(float width);

int main() {
  initialize();
  while (window.isOpen()) {
    events();
    update();
    render();
  }
}

void initialize() {
  window.create(sf::VideoMode({1920, 1080}), "Flying Pan!",
                sf::State::Fullscreen);
  window.setFramerateLimit(30);

  player = initializePlayer();
  ground = initializeGround(window.getSize().x * 1.0f);
}

void events() {
  delta_time = game_clock.restart().asSeconds();

  while (std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (event->is<sf::Event::KeyPressed>()) {
      switch (event->getIf<sf::Event::KeyPressed>()->scancode) {
        case sf::Keyboard::Scan::Escape:
          window.close();
          break;
        case sf::Keyboard::Scan::Space:
          speed_up_cooldown = 0.0f;
          break;
        case sf::Keyboard::Scan::Up:
          if (current_level < HeightLevel.size() - 1) {
            current_level++;
          }
          break;
        case sf::Keyboard::Scan::Down:
          if (current_level > 0) {
            current_level--;
          }
        default:
          break;
      }
    }
  }
}

void update() {
  spawn_time -= delta_time;
  if (spawn_time <= 0) {
    generateObstacle();
    spawn_time = (speed_level > 3) ? 0.6f : 1.5f - (speed_level * 0.3f);
  }

  speed_up_cooldown -= delta_time;
  if (speed_up_cooldown <= 0) {
    obstacle_speed += -100.0f;
    speed_up_cooldown = 5.0f;
    speed_level++;
  }

  player.setPosition({200.0f, HeightLevel[current_level]});
  for (auto& obstacle : obstacles) {
    obstacle.move({obstacle_speed * delta_time, 0});
    if (obstacle.getGlobalBounds().findIntersection(player.getGlobalBounds()))
      window.close();
  }
}

void render() {
  window.clear();
  window.draw(player);
  window.draw(ground);
  for (auto& obstacle : obstacles) {
    window.draw(obstacle);
  }
  window.display();
}

sf::RectangleShape initializePlayer() {
  sf::RectangleShape player({150.0f, 150.0f});
  player.setOrigin(player.getGeometricCenter());
  player.setPosition({200.0f, kGroundLevel});
  player.setOutlineColor(sf::Color::Green);
  player.setOutlineThickness(2.0f);

  return player;
}

sf::RectangleShape initializeGround(float width) {
  sf::RectangleShape ground({width, 50});

  ground.setFillColor(sf::Color::Red);
  ground.setPosition({0, kGroundLevel});
  ground.setOutlineThickness(1.5f);
  ground.setOutlineColor(sf::Color::Magenta);

  return ground;
}

void generateObstacle() {
  int height_level{0};
  if (obstacles.size() % 2 == 0) {
    if (used_height[0] + used_height[1] == 1) {
      height_level = rand() % 2;
    } else if (used_height[0] + used_height[1] == 2) {
      height_level = (rand() % 2) ? 0 : 2;
    } else if (used_height[0] + used_height[1] == 3) {
      height_level = rand() % 3 + 1;
    }
    used_height[0] = height_level;
  } else {
    height_level = rand() % 3;
    used_height[1] = height_level;
  }

  int point_count = rand() % 8 + 3;

  sf::CircleShape obstacle(50);
  obstacle.setOrigin(obstacle.getGeometricCenter());
  obstacle.setPosition(
      {window.getSize().x + 100.0f, HeightLevel[height_level]});
  obstacle.setPointCount(point_count);
  obstacle.setOutlineThickness(5);
  obstacle.setOutlineColor(sf::Color::Red);
  obstacles.emplace_back(obstacle);
}