#include "game.h"
#include "map.h"
Game::Game()
  :window(sf::VideoMode(1200, 1200), "MyGame"){}


void Game::run(){
  Map::Map map;
  while(window.isOpen()){
    processEvents();
    //update();
    render(map);
  }
}

void Game::processEvents(){
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
  }
}

void Game::render(Map map){
  window.clear();
  for(auto&& i : map.lines){
    window.draw(i);
  }
  window.display();
}

