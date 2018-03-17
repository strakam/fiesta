#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include <vector>

class Game{
 public:
  Game();
  void run();
 private:
  void processEvents();
  void update();
  void render(Map map);

  sf::RenderWindow window;
  std::vector<int> players;
};
