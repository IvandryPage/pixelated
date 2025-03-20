#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML Template!",
                          sf::State::Fullscreen);
  window.setFramerateLimit(60);

  const auto OnClosed = [&window](const sf::Event::Closed&) { window.close(); };

  const auto OnKeyPressed =
      [&window](const sf::Event::KeyPressed& key_pressed) {
        if (key_pressed.scancode == sf::Keyboard::Scancode::Escape) {
          window.close();
        }
      };

  sf::RectangleShape rect({200, 200});
  rect.setPosition({100, 100});
  rect.setFillColor(sf::Color(255, 255, 255));
  rect.setOrigin(rect.getGeometricCenter());

  sf::CircleShape circle(100);
  circle.setPosition({150, 150});
  circle.setFillColor(sf::Color(128, 128, 128));
  circle.setOrigin(circle.getGeometricCenter());

  sf::CircleShape triangle(100);
  triangle.setPointCount(3);
  triangle.setPosition({200, 200});
  triangle.setFillColor({255, 0, 0});
  triangle.setOrigin(triangle.getGeometricCenter());

  std::vector<sf::CircleShape> hexagon;
  for (int i = 0; i <= 10; i++) {
    sf::CircleShape s(i * 150 * 0.2f);
    s.setFillColor(sf::Color(i * 10, i * 15, i * 12));
    s.setPosition({i * 50.0f + 300.0f, i * 25.0f + 500});
    s.setPointCount(10 - i);
    s.setOrigin(s.getGeometricCenter());
    hexagon.push_back(s);
  }

  while (window.isOpen()) {
    // Events Handler
    window.handleEvents(OnClosed, OnKeyPressed);

    // Updates
    rect.setRotation(rect.getRotation() + sf::Angle(sf::degrees(5)));
    circle.setRotation(circle.getRotation() + sf::Angle(sf::degrees(20)));
    triangle.setRotation(triangle.getRotation() + sf::Angle(sf::degrees(10)));

    for (size_t i = 0; i < std::size(hexagon); i++) {
      hexagon[i].setRotation(hexagon[i].getRotation() +
                             sf::Angle(sf::degrees(i * 2)));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      circle.setPosition(
          {circle.getPosition().x - 10.0f, circle.getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      circle.setPosition(
          {circle.getPosition().x + 10.0f, circle.getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      circle.setPosition(
          {circle.getPosition().x, circle.getPosition().y - 10.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      circle.setPosition(
          {circle.getPosition().x, circle.getPosition().y + 10.0f});
    }

    // Render
    window.clear(sf::Color(255, 255, 255));
    window.draw(rect);
    window.draw(circle);
    window.draw(triangle);

    for (auto s : hexagon) {
      window.draw(s);
    }

    window.display();
  }
}