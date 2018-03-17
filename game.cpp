#include "game.h"
Game::Game()
  :window(sf::VideoMode(800, 800), "MyGame"){}


void Game::run(){
  while(window.isOpen()){
    processEvents();
    //update();
    render();
  }
}

void Game::processEvents(){
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
  }
}

void Game::render(){
  window.clear();
  window.display();
}
