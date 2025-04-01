#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Texture Demo",
                          sf::State::Fullscreen);
  window.setFramerateLimit(60);

  sf::Clock clock;
  float speed_anim = 0.11f;
  int frame = 0;
  const int frameWidth = 32;
  const int numFrames = 11;

  sf::Texture character("assets/Main Characters/Virtual Guy/Run (32x32).png");
  sf::Sprite v_guy(character);
  v_guy.setTextureRect(sf::IntRect({frame * frameWidth, 0}, {frameWidth, 32}));
  v_guy.scale({10.0f, 10.0f});

  int i = 0;
  while (window.isOpen()) {
    // float delta_time = clock.restart().asSeconds();
    while (std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();

      if (event->is<sf::Event::KeyPressed>())
        if (event->getIf<sf::Event::KeyPressed>()->scancode ==
            sf::Keyboard::Scan::Escape)
          window.close();
    }

    if (clock.getElapsedTime().asSeconds() >= speed_anim) {
      clock.restart();
      frame = frame % numFrames;
      v_guy.setTextureRect(
          sf::IntRect({frame * frameWidth, 0}, {frameWidth, 32}));
      frame++;
    }

    window.clear(sf::Color::Black);
    window.draw(v_guy);
    window.display();
  }
  return 0;
}