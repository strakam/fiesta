#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
class Game{
 public:
  Game();
  void run();
 private:
  void processEvents();
  void update();
  void render();

  sf::RenderWindow window;
  std::vector<int> players;
};
