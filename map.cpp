#include "map.h"

Map::Map(){
  // Initialization of variables
  createLines(lines);
  createSquares(squares);
}

void Map::createLines(std::vector<sf::RectangleShape>& lines){
  // Creating lines
  int x = 75, y = 0;
  for(int i = 0; i < 15; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(1200, 1)));
    lines[i].setPosition(200, x);
    lines[i].setFillColor(sf::Color(192, 192, 192));
    x += 75;
  }
  for(int i = 0; i < 17; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(1, 1200)));
    lines[i+15].setFillColor(sf::Color(192, 192, 192));
    lines[i+15].setPosition(200+y, 0);
    y += 75;
  }
}

void Map::createSquares(vector<vector<int> >& squares){
  // Creating Map where game is calculated.
  squares.resize(16);
  for(int i = 0; i < squares.size(); i++){
    for(int x = 0; x < 16; x++)
      squares[i].push_back(0);
  }
}
