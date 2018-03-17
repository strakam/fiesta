#ifndef MAP_H
#define MAP_H
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Map{
 public:
  Map();
  std::string name = "name";
  std::vector<sf::RectangleShape> lines;
  void createLines(std::vector<sf::RectangleShape>& lines);
};
#endif //MAP_H
