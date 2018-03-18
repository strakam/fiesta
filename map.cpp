#include "map.h"

Map::Map(){
  createLines(lines);
  createSquares(squares);
}

void Map::createLines(std::vector<sf::RectangleShape>& lines){
  int x = 65, y = 65;
  for(int i = 0; i < 16; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(1200, 5)));
    lines[i].setPosition(0, x);
    lines[i].setFillColor(sf::Color(192, 192, 192));
    x += 70;
  }
  for(int i = 0; i < 16; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(5, 1200)));
    lines[i+16].setFillColor(sf::Color(192, 192, 192));
    lines[i+16].setPosition(y, 0);
    y += 70;
  }
}

void Map::createSquares(vector<vector<int> >& squares){
  squares.resize(16);
  for(int i = 0; i < squares.size(); i++){
    for(int x = 0; x < 17; x++)
      squares[i].push_back(0);
  }
}
