#include "player.h"

Player::Player(int xcord, int ycord){
  x = xcord;
  y = ycord;
}

bool Player::isOut(){
  if(x > 23 || x < 0 || y > 23 || y < 0)
    return true;
  else return false;
}
