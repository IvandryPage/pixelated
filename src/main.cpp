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

  while (window.isOpen()) {
    // Events Handler
    window.handleEvents(OnClosed, OnKeyPressed);

    // Updates

    // Render
    window.clear();
    window.display();
  }
}