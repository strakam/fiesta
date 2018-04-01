#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "map.h"
#include "player.h"
#include <vector>

using namespace sf;

class Game{
 public:
  Game();
  void run();
 private:
  void processEvents(Player& p1, Player& p2, int players, Map map);
  void update(Map& map, Player& p1, Player& p2);
  void render(Map map, Player& p1, Player& p2);
  void checkWin(Map map, Player p1, Player p2);
  void setFonts(Font& font, Text& pvptext, Text& pvetext, Text& exittext, Text& info, Text& cp);
  int preGameEvents();
  void Options(Font& font, Text& pvptext, Text& pvetext, Text& exittext, Sprite& background, Text& info, Text& cp);
  int preGame();

  
  bool running;
  int wLength = 1700, wHeight = 1200;
  int m1 [2] = {0, 0}; int m2 [2] = {0, 0};
  sf::RenderWindow window;
  std::vector<int> players;
};
