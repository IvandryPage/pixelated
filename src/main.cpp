#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

constexpr float kGroundLevel = 500.0f;
std::array<float, 3> HeightLevel{400.0f, 250.0f, 100.0f};
size_t current_level{0};
bool game_over{false};
bool is_running{true};

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
size_t score{0};

sf::Font font("assets/ShareTechMono-Regular.ttf");
std::vector<sf::Text> texts;

void initialize();
void events();
void update();
void render();
void generateObstacle();
sf::RectangleShape initializePlayer();
sf::RectangleShape initializeGround(float width);

int main() {
  srand(time(0));
  initialize();
  while (window.isOpen()) {
    events();
    if (is_running) {
      update();
    }
    render();
  }
}

void initialize() {
  window.create(sf::VideoMode({1920, 1080}), "Flying Pan!",
                sf::State::Fullscreen);
  window.setFramerateLimit(30);

  player = initializePlayer();
  ground = initializeGround(window.getSize().x * 1.0f);

  texts.push_back(sf::Text(font, "Score  : " + std::to_string(score), 24));
  texts.push_back(
      sf::Text(font, "Speed+ : " + std::to_string(speed_up_cooldown), 24));
  texts.push_back(sf::Text(font, "Spawn  : " + std::to_string(spawn_time), 24));
  texts.push_back(
      sf::Text(font, "Obstacles  : " + std::to_string(obstacles.size()), 24));

  texts.push_back(sf::Text(font, "GAME OVER!\nPress Escape to exit!", 30));
  texts.push_back(
      sf::Text(font, "Press Up and Down arrow on keyboard to move", 30));

  texts[0].setPosition({100, 700});
  texts[1].setPosition({100, 800});
  texts[2].setPosition({100, 900});
  texts[3].setPosition({400, 700});
  texts[4].setPosition({600, 800});
  texts[5].setPosition({100, 500});
}

void events() {
  delta_time = game_clock.restart().asSeconds();
  obstacles.remove_if(
      [](const sf::CircleShape& c) { return c.getPosition().x < 0; });

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
          is_running = !is_running;
          game_over = false;
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
    obstacle.rotate(sf::Angle(sf::degrees(-10.0f)));
    if (obstacle.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
      game_over = true;
      is_running = false;
    }
    if (player.getPosition().x > obstacle.getPosition().x) {
      score++;
    }
  }

  texts[0].setString("Score  : " + std::to_string(score));
  texts[1].setString("Speed+ : " + std::to_string(speed_up_cooldown));
  texts[2].setString("Spawn  : " + std::to_string(spawn_time));
  texts[3].setString("Obstacles  : " + std::to_string(obstacles.size()));
}

void render() {
  window.clear();
  window.draw(player);
  window.draw(ground);
  for (auto& obstacle : obstacles) {
    window.draw(obstacle);
  }
  for (auto& text : texts) {
    if (text.getString().find("GAME OVER")) {
      window.draw(text);
    }
  }

  if (game_over) {
    window.draw(texts[4]);
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

  sf::CircleShape obstacle(35);
  obstacle.setOrigin(obstacle.getGeometricCenter());
  obstacle.setPosition(
      {window.getSize().x + 100.0f, HeightLevel[height_level]});
  obstacle.setPointCount(point_count);
  obstacle.setOutlineThickness(5);
  obstacle.setOutlineColor(sf::Color::Red);
  obstacles.emplace_back(obstacle);
}