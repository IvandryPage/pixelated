#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML Template!",
                          sf::State::Fullscreen);
  window.setFramerateLimit(60);
  std::list<sf::CircleShape> entity;
  int speed = rand() % 250 + 100;

  const auto OnClosed = [&window](const sf::Event::Closed&) { window.close(); };

  const auto OnKeyPressed =
      [&window](const sf::Event::KeyPressed& key_pressed) {
        if (key_pressed.scancode == sf::Keyboard::Scancode::Escape) {
          window.close();
        }
      };

  const auto OnMouseButtonPressed =
      [&](const sf::Event::MouseButtonPressed& button_pressed) {
        // if (button_pressed.button == sf::Mouse::Button::Middle) {
        //   sf::CircleShape shape(100.0f);
        //   shape.setOrigin(shape.getGeometricCenter());
        //   shape.setPosition({sf::Mouse::getPosition(window).x * 1.0f,
        //                      sf::Mouse::getPosition(window).y * 1.0f});
        //   shape.setPointCount(rand() % 8 + 3);
        //   shape.setFillColor(
        //       sf::Color(rand() % 255, rand() % 255, rand() % 255));
        //   entity.emplace_back(shape);
        // }
        if (button_pressed.button == sf::Mouse::Button::Right) {
          entity.remove_if([&](const sf::CircleShape& shape) {
            return shape.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)));
          });
        }
      };

  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    // Events Handler
    window.handleEvents(OnClosed, OnKeyPressed, OnMouseButtonPressed);

    // Updates
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      for (auto& e : entity) {
        if (e.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
          e.setPosition(
              window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
      for (size_t i = 0; i < 7; i++) {
        sf::CircleShape shape(rand() % 15 + 1.0f);
        shape.setOrigin(shape.getGeometricCenter());
        shape.setPosition(
            {sf::Mouse::getPosition(window).x + (rand() % 100 + 70) * 1.0f,
             sf::Mouse::getPosition(window).y + (rand() % 150 + 50) * 1.0f});
        shape.setPointCount(rand() % 8 + 6);
        shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        entity.emplace_back(shape);
      }
    }

    for (auto& e : entity) {
      e.setPosition({e.getPosition().x, e.getPosition().y + speed * dt});
    }

    entity.remove_if([&](sf::CircleShape& shape) {
      return shape.getPosition().y > window.getSize().y;
    });

    std::cout << "entity count: " << entity.size() << std::endl;

    // Render
    window.clear();
    for (auto& e : entity) {
      window.draw(e);
    }
    window.display();
  }
}