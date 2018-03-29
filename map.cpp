#include "map.h"

Map::Map(){
  // Initialization of variables
  createLines(lines);
  createSquares(squares);
}

void Map::createLines(std::vector<sf::RectangleShape>& lines){
  // Creating lines
  int x = 50, y = 0;
  for(int i = 0; i < 23; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(1200, 1)));
    lines[i].setPosition(250, x);
    lines[i].setFillColor(sf::Color(192, 192, 192));
    x += 50;
  }
  for(int i = 0; i < 25; i++){
    lines.push_back(sf::RectangleShape (sf::Vector2f(1, 1200)));
    lines[i+23].setFillColor(sf::Color(192, 192, 192));
    lines[i+23].setPosition(250+y, 0);
    y += 50;
  }
}

void Map::createSquares(vector<vector<int> >& squares){
  // Creating Map where game is calculated.
  squares.resize(24);
  for(int i = 0; i < squares.size(); i++){
    for(int x = 0; x < 24; x++)
      squares[i].push_back(0);
  }
}
