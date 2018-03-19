#include "game.h"
#include "map.h"
#include "player.h"
#include <cstdlib>
#include <time.h>

Game::Game()
  :window(sf::VideoMode(1200, 1200), "MyGame"){}

void Game::run(){
  // Creating Players & Map
  std::srand(time(NULL));
  Map::Map map;
  int posX = rand()%16, posY = rand()%16;
  int posY2 = 15 - posY;
  Player::Player p1(posX, posY);
  Player::Player p2(posX, posY2);
  map.squares[posY2][posX] = 2;
  map.squares[posY][posX] = 1;
  // Main game loop
   while(window.isOpen()){
     processEvents(p1, p2);
     update(map, p1, p2);
     render(map);
  }
}

void Game::processEvents(Player& p1, Player& p2){
  // Processing Keyboard events
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
    else if(event.type == sf::Event::KeyPressed){
      if(event.key.code == sf::Keyboard::W)
	p1.x--;
      else if(event.key.code == sf::Keyboard::A)
        p1.y--;
      else if(event.key.code == sf::Keyboard::S)
	p1.x++;
      else if(event.key.code == sf::Keyboard::D)
	p1.y++;
      else if(event.key.code == sf::Keyboard::I)
	p2.x--;
      else if(event.key.code == sf::Keyboard::J)
	p2.y--;
      else if(event.key.code == sf::Keyboard::K)
	p2.x++;
      else if(event.key.code == sf::Keyboard::L)
	p2.y++;
    }
  }
}

void Game::render(Map map){
  window.clear();
  // Draw player trails
  sf::RectangleShape p1trail(sf::Vector2f(75, 75));
  p1trail.setFillColor(sf::Color(232, 12, 122));
  sf::RectangleShape p2trail(sf::Vector2f(75, 75));
  p2trail.setFillColor(sf::Color(12, 89, 232));
  for(int y = 0; y < 16; y++){
    for(int x = 0; x < 16; x++){
      if(map.squares[y][x] == 1){
	p1trail.setPosition(y*75, x*75);
	window.draw(p1trail);
      }
      else if(map.squares[y][x] == 2){
	p2trail.setPosition(y*75, x*75);
	window.draw(p2trail);
      }
    }
  }
  // Draw lines
  for(auto&& i : map.lines){
    window.draw(i);
  }
  window.display();
}

void Game::update(Map& map, Player p1, Player p2){
  // Update status of map
  map.squares[p1.y][p1.x] = 1;
  map.squares[p2.y][p2.x] = 2;
}
