#include "map.h"

Map::Map(){
  createLines(lines);
}

void Map::createLines(std::vector<sf::RectangleShape>& lines){
  int x = 70, y = 70;
  for(int i = 0; i < 16; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(1200, 5)));
    lines[i].setPosition(0, x);
    lines[i].setFillColor(sf::Color(255, 255, 255));
    x += 70;
  }
  for(int i = 0; i < 16; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(5, 1200)));
    lines[i+16].setFillColor(sf::Color(255, 255, 255));
    lines[i+16].setPosition(y, 0);
    y += 70;
  }
}
