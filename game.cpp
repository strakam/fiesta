#include "game.h"
#include "map.h"
#include "player.h"
#include <cstdlib>
#include <time.h>eeeeeeeeeeeeeeeeee

Game::Game()
  :window(sf::VideoMode(1185, 1185), "MyGame"){}


void Game::run(){
  std::srand(time(NULL));
  Map::Map map;
  Player::Player p1(rand()%17, rand()%17);
   while(window.isOpen()){
    processEvents();
    //update()
    render(map, p1);
  }
}

void Game::processEvents(){
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
  }
}

void Game::render(Map map, Player p1){
  window.clear();
  for(auto&& i : map.lines){
    window.draw(i);
  }
  sf::RectangleShape shit(sf::Vector2f(120, 50));
  shit.setFillColor(sf::Color(255, 255, 255));
  shit.setPosition(p1.x*50, p1.y*50);
  window.draw(shit);
  window.display();
}
