#ifndef MAP_H
#define MAP_H
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
class Map{
 public:
  Map();
  std::vector<sf::RectangleShape> lines;
  std::vector<vector<int> > squares;
  
  void createSquares(std::vector<vector<int> >& squares);
  void createLines(std::vector<sf::RectangleShape>& lines);
};
#endif //MAP_H
