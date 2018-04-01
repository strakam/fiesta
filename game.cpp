#include "game.h"
#include "map.h"
#include "player.h"
#include <cstdlib>
#include <time.h>
#include <thread>

Game::Game()
  :window(sf::VideoMode(wLength, wHeight), "MyGame"){}

void Game::run(){
  running =  false;
  // Main game loop
   while(window.isOpen()){
     if(!running){
       int players = preGame();
       std::srand(time(NULL));
       Map map;
       sf::Clock clock;
       int posX = rand()%24, posY = rand()%24;
       int posX2 = 23 - posX;
       Player p1(posY, posX);
       Player p2(posY, posX2);
       map.squares[posY][posX2] = 2;
       map.squares[posY][posX] = 1;
       if(posY > 11){
	 m1[0] = -1; m1[1] = 0;
	 m2[0] = -1; m2[1] = 0;
       }
       else{
	 m1[0] = 1; m1[1] = 0;
	 m2[0] = 1; m2[1] = 0;
       }
       running = true;
       sf::Music music;
       int randmusic = rand()%3;
       if(randmusic == 0)
	 music.openFromFile("sounds/takeonme.ogg");
       else if(randmusic == 1)
	 music.openFromFile("sounds/witch.ogg");
       else if(randmusic == 2)
	 music.openFromFile("sounds/partytroll.ogg");
       music.play();
       while(window.isOpen() && running == true){
	 processEvents(p1, p2, players, map);
	 update(map, p1, p2);
	 render(map, p1, p2);
       }
     }
  }
}
void Game::render(Map map, Player& p1, Player& p2){
  window.clear();
  // Draw player trails
  sf::RectangleShape p1trail(sf::Vector2f(50, 50));
  p1trail.setFillColor(sf::Color(217, 206, 176));
  sf::RectangleShape p2trail(sf::Vector2f(50, 50));
  p2trail.setFillColor(sf::Color(139, 255, 141));
  for(int y = 0; y < 24; y++){
    for(int x = 0; x < 24; x++){
      if(map.squares[y][x] == 1){
	p1trail.setPosition(x * 50 + 250, y * 50);
	window.draw(p1trail);
      }
      else if(map.squares[y][x] == 2){
	p2trail.setPosition(x * 50 + 250, y * 50);
	window.draw(p2trail);
      }
    }
  }
  // Draw 'heads' of players
  sf::Texture doge;
  doge.loadFromFile("pics/dogep.png");
  sf::RectangleShape p1current(sf::Vector2f(50, 50));
  p1current.setTexture(&doge);
  p1current.setPosition(p1.x*50 + 250, p1.y*50);

  sf::Texture pepe;
  pepe.loadFromFile("pics/pepef.jpg");
  sf::RectangleShape p2current(sf::Vector2f(50, 50));
  p2current.setPosition(p2.x*50 + 250, p2.y*50);
  p2current.setTexture(&pepe);
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
  if(Player::isOut(p1.y, p1.x) || map.squares[p1.y][p1.x] != 0){
    if(Player::isOut(p2.y, p2.x) || map.squares[p2.y][p2.x] != 0){
      window.setTitle("Tie!");
      running = false;
    }
    else{
      window.setTitle("P2 Wonnered!");
      running = false;
    }
  }
  else if(Player::isOut(p2.y, p2.x) || map.squares[p2.y][p2.x] != 0){
    window.setTitle("P1 Wonnered!");
    running = false;
  }
  else{
    map.squares[p1.y][p1.x] = 1;
    map.squares[p2.y][p2.x] = 2;
  }
}

void Game::processEvents(Player& p1, Player& p2, int players, Map map){
  // Processing Keyboard events
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
  }
  if(players == 1){
    p2.x2 = p1.x; p2.y2 = p1.y;
    p2.botmap = map.squares;
    sf::Thread bot (&Player::calculate, &p2);
    bot.launch();
  }
  sf::Clock clock;
  while(clock.getElapsedTime().asMilliseconds() < 200){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
      if(m1[1] == 0) continue;
      m1[0] = -1; m1[1] = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      if(m1[0] == 0) continue;
      m1[0] = 0; m1[1] = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
      if(m1[1] == 0) continue;
      m1[0] = 1; m1[1] = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      if(m1[0] == 0) continue;
      m1[0] = 0; m1[1] = 1;
    }
    if(players == 2){
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
	if(m2[1] == 0) continue;
	m2[0] = -1; m2[1] = 0;
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
	if(m2[0] == 0) continue;
	m2[0] = 0; m2[1] = -1;
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
	if(m2[1] == 0) continue;
	m2[0] = 1; m2[1] = 0;
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
	if(m2[0] == 0) continue;
	m2[0] = 0; m2[1] = 1;
      }
    }
  }
}


void Game::setFonts(Font& font, Text& pvptext, Text& pvetext, Text& exittext, Text& info, Text& cp){
  pvptext.setFont(font);
  pvetext.setFont(font);
  exittext.setFont(font);
  info.setFont(font);
  cp.setFont(font);

  pvptext.setString("PVP");
  pvetext.setString("PVE");
  exittext.setString("Exit");
  info.setString("This shit was created and raised by Matej Straka.");
  cp.setString("All rights reserved.");

  pvptext.setCharacterSize(30);
  pvetext.setCharacterSize(30);
  exittext.setCharacterSize(30);
  info.setCharacterSize(30);
  cp.setCharacterSize(30);
  
  pvptext.setFillColor(sf::Color::Black);
  pvetext.setFillColor(sf::Color::Black);
  exittext.setFillColor(sf::Color::Black);
  info.setFillColor(sf::Color::White);
  cp.setFillColor(sf::Color::White);

  int x = 820;
  pvptext.setPosition(x, 430);
  pvetext.setPosition(x, 630);
  exittext.setPosition(x, 830);
  info.setPosition(470, 1100);
  cp.setPosition(670, 1150);
}

int Game::preGame(){
  sf::Sprite bg;
  sf::Texture texture;
  texture.loadFromFile("pics/pepedoge.png");
  bg.setTexture(texture);
  sf::Font font;
  font.loadFromFile("fonts/OpenSans-Bold.ttf");
  sf::Text pvptext, pvetext, exittext, info, cp;
  setFonts(font, pvptext, pvetext, exittext, info, cp);
  int players = 0;

  while(window.isOpen() && players == 0){
    Options(font, pvptext, pvetext, exittext, bg, info, cp);
    players = preGameEvents();
  }
  return players;
}

int Game::preGameEvents(){
  sf::Event event;
  while(window.pollEvent(event)){
    if(event.type == sf::Event::Closed)
      window.close();
    if(event.type == sf::Event::MouseButtonPressed){
      if(event.mouseButton.button == sf::Mouse::Left){
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if(mousePos.x > 750 && mousePos.x < 950){
	  if(mousePos.y > 400 && mousePos.y < 500)
	    return 2;
	  else if(mousePos.y > 600 && mousePos.y < 700)
	    return 1;
	  else if(mousePos.y > 800 && mousePos.y < 900)
	    window.close();
	}
      }
    }
    if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      return 1;
  }
  return 0;
}

void Game::Options(Font& font, Text& pvptext, Text& pvetext, Text& exittext, Sprite& background, Text& info, Text& cp){
  window.clear();
  window.draw(background);
  int x = 750, y = 400;
  sf::RectangleShape pvpSquare1(sf::Vector2f(200, 100));
  pvpSquare1.setPosition(x, y);
  pvpSquare1.setFillColor(sf::Color(255, 255, 255));
  pvpSquare1.setOutlineThickness(5);
  pvpSquare1.setOutlineColor(sf::Color(0, 0, 0));
  window.draw(pvpSquare1);
  sf::RectangleShape pvpSquare2(sf::Vector2f(200, 100));
  pvpSquare2.setFillColor(sf::Color(255, 255, 255));
  pvpSquare2.setPosition(x, y+200);
  pvpSquare2.setOutlineThickness(5);
  pvpSquare2.setOutlineColor(sf::Color(0, 0, 0));
  window.draw(pvpSquare2);
  sf::RectangleShape pvpSquare3(sf::Vector2f(200, 100));
  pvpSquare3.setPosition(x, y+400);
  pvpSquare3.setFillColor(sf::Color(255, 255, 255));
  pvpSquare3.setOutlineThickness(5);
  pvpSquare3.setOutlineColor(sf::Color(0, 0, 0));
  window.draw(pvpSquare3);

  window.draw(pvptext);
  window.draw(pvetext);
  window.draw(exittext);
  window.draw(info);
  window.draw(cp);
  
  window.display();
}
