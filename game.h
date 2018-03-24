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
  void update(Map& map, Player& p1, Player& p2);
  void render(Map map, Player& p1, Player& p2);
  void checkWin(Map map, Player p1, Player p2);

  bool running;
  int m1 [2] = {0, 0}; int m2 [2] = {0, 0};
  sf::RenderWindow window;
  std::vector<int> players;
};
