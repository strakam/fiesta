#include "game.h"
#include "map.h"
#include "player.h"
#include <cstdlib>
#include <time.h>

Game::Game()
  :window(sf::VideoMode(1185, 1185), "MyGame"){}


void Game::run(){
  std::srand(time(NULL));
  Map::Map map;
  int posX = rand()%17, posY = rand()%17;
  Player::Player p1(posX, posY);
  map.squares[posY][posX] = 1;
   while(window.isOpen()){
    processEvents(p1);
    update(map, p1);
    render(map, p1);
  }
}

void Game::processEvents(Player& p1){
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
    }
  }
}

void Game::render(Map map, Player p1){
  window.clear();
  // Draw lines
  for(auto&& i : map.lines){
    window.draw(i);
  }
  // Draw player trails
  sf::RectangleShape p1trail(sf::Vector2f(70, 70));
  p1trail.setFillColor(sf::Color(232, 12, 122));
  for(int y = 0; y < 16; y++){
    for(int x = 0; x < 16; x++){
      if(map.squares[y][x] == 1){
	p1trail.setPosition(y*75, x*75);
	window.draw(p1trail);
      }
      else if(map.squares[y][x] == 2){
	
      }
    }
  }
  window.display();
}

void Game::update(Map& map, Player p1){
  map.squares[p1.y][p1.x] = 1;
}
