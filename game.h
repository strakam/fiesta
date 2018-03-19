#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "player.h"
#include <vector>

class Game{
 public:
  Game();
  void run();
 private:
  void processEvents(Player& p1, Player& p2);
  void update(Map& map, Player p1, Player p2);
  void render(Map map);

  sf::RenderWindow window;
  std::vector<int> players;
};
