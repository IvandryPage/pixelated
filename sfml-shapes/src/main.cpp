#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML Template!",
                          sf::State::Fullscreen);
  window.setFramerateLimit(60);

  sf::RectangleShape rect({200, 200});
  rect.setPosition({100, 100});
  rect.setFillColor(sf::Color(255, 255, 255));
  rect.setOrigin(rect.getGeometricCenter());

  sf::CircleShape circle(50);
  circle.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
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

  const auto OnClosed = [&window](const sf::Event::Closed&) { window.close(); };

  const auto OnKeyPressed =
      [&window, &circle, &hexagon](const sf::Event::KeyPressed& key_pressed) {
        if (key_pressed.scancode == sf::Keyboard::Scancode::Escape) {
          window.close();
        }
        if (key_pressed.scancode == sf::Keyboard::Scancode::Space) {
          for (int i = 0; i <= 10; i++) {
            sf::CircleShape s(i * 150 * 0.2f);
            s.setFillColor(sf::Color(i * 10, i * 15, i * 12));
            s.setPosition({i * 50.0f + circle.getPosition().x,
                           i * 25.0f + circle.getPosition().y});
            s.setPointCount(10 - i);
            s.setOrigin(s.getGeometricCenter());
            hexagon.push_back(s);
          }
        }
      };

  while (window.isOpen()) {
    // Events Handler
    window.handleEvents(OnClosed, OnKeyPressed);

    // Updates
    circle.setPosition({circle.getPosition().x, circle.getPosition().y + 1.0f});
    rect.setRotation(rect.getRotation() + sf::Angle(sf::degrees(5)));
    circle.setRotation(circle.getRotation() + sf::Angle(sf::degrees(20)));
    triangle.setRotation(triangle.getRotation() + sf::Angle(sf::degrees(10)));

    for (size_t i = 0; i < std::size(hexagon); i++) {
      hexagon[i].setRotation(hexagon[i].getRotation() +
                             sf::Angle(sf::degrees(i * 2)));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
      circle.setPosition(
          {circle.getPosition().x - 10.0f, circle.getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      circle.setPosition(
          {circle.getPosition().x + 10.0f, circle.getPosition().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      circle.setPosition(
          {circle.getPosition().x, circle.getPosition().y - 10.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      circle.setPosition(
          {circle.getPosition().x, circle.getPosition().y + 10.0f});
    }

    // Render
    window.clear();
    window.draw(rect);
    window.draw(circle);
    window.draw(triangle);

    for (auto s : hexagon) {
      window.draw(s);
    }

    window.display();
  }
}