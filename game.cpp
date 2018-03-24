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
  sf::Time turn = sf::milliseconds(300);
  Map::Map map;
  sf::Clock clock;
  int posX = rand()%16, posY = rand()%16;
  int posY2 = 15 - posY;

  Player::Player p1(posX, posY);
  Player::Player p2(posX, posY2);
  map.squares[posY2][posX] = 2;
  map.squares[posY][posX] = 1;
  if(posX > 7){
    m1[0] = 0; m1[1] = -1;
    m2[0] = 0; m2[1] = -1;
  }
  else{
    m1[0] = 0; m1[1] = 1;
    m2[0] = 0; m2[1] = 1;
  }
  
  running =  true;
  // Main game loop
   while(window.isOpen()){
     processEvents(p1, p2);
     if(running) update(map, p1, p2);
     render(map, p1, p2);
     clock.restart();
  }
}


void Game::render(Map map, Player& p1, Player& p2){
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
  // Draw 'heads' of players
  sf::RectangleShape p1current(sf::Vector2f(75, 75));
  p1current.setFillColor(sf::Color(61, 0, 70));
  p1current.setPosition(p1.y*75, p1.x*75);
  sf::RectangleShape p2current(sf::Vector2f(75, 75));
  p2current.setPosition(p2.y*75, p2.x*75);
  p2current.setFillColor(sf::Color(21, 28, 135));
  window.draw(p1current);
  window.draw(p2current);
  // Draw lines
  for(auto&& i : map.lines){
    window.draw(i);
  }
  window.display();
}

void Game::update(Map& map, Player& p1, Player& p2){
  // Update status of map
  p1.y += m1[0]; p1.x += m1[1];
  p2.y += m2[0]; p2.x += m2[1];
  if(p1.isOut() || map.squares[p1.y][p1.x] != 0){
    if(p2.isOut() || map.squares[p2.y][p2.x] != 0){
      window.setTitle("Tie!");
      running = false;
    }
    else{
      window.setTitle("P2 Wonnered!");
      running = false;
    }
  }
  else if(p2.isOut() || map.squares[p2.y][p2.x] != 0){
    window.setTitle("P1 Wonnered!");
    running = false;
  }
  else{
    map.squares[p1.y][p1.x] = 1;
    map.squares[p2.y][p2.x] = 2;
  }
}

void Game::processEvents(Player& p1, Player& p2){
  // Processing Keyboard events
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
  }
  sf::Clock clock;
  while(clock.getElapsedTime().asMilliseconds() < 300){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      if(m1[0] == 0) continue;
      m1[0] = 0; m1[1] = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      if(m1[1] == 0) continue;
      m1[0] = -1; m1[1] = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      if(m1[0] == 0) continue;
      m1[0] = 0; m1[1] = 1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      if(m1[1] == 0) continue;
      m1[0] = 1; m1[1] = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
      if(m2[1] == 1) continue;
      m2[0] = 0; m2[1] = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
      if(m2[0] == 1) continue;
      m2[0] = -1; m2[1] = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
      if(m2[1] == -1) continue;
      m2[0] = 0; m2[1] = 1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
      if(m2[0] == -1) continue;
      m2[0] = 1; m2[1] = 0;
    }
  }
}
