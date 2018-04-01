#include "player.h"

Player::Player(int ycord, int xcord){
  x = xcord;
  y = ycord;
  inidirs();
}

bool Player::isOut(int y, int x){
  if(x > 23 || x < 0 || y > 23 || y < 0)
    return true;
  else return false;
}

void Player::inidirs(){
  dir[0][0] = -1; //Up
  dir[0][1] = 0;
  dir[1][0] = 1; //Down
  dir[1][1] = 0;
  dir[2][0] = 0; //Left
  dir[2][1] = -1;
  dir[3][0] = 0;
  dir[3][1] = 1; //Right
}

void Player::calculate(){
  for(int i = 0; i < 24; i++){
    for(int x = 0; x < 24; x++)
      printf("%d ", botmap[i][x]);
    printf("\n");
  }
  printf("\n");/*
  deque<pair<int, int> > botsearch;
  vector<vector<pair<int, int> > > pmap;
  pmap.resize(24);
  for(int i = 0; i < 24; i++)
    for(int x = 0; x < 24; x++)
      pmap[i].push_back(make_pair(0, 0));      
  int bcount = 0, pcount = 0;
  int ways[4][2];
  for(int i = 0; i < 4; i++){
    ways[i][0] = 0;
    ways[i][1] = 0;
  }
  //bot's bfs
  for(int i = 0; i < 4; i++){
    int tx = x + dir[i][1], ty = y + dir[i][0];
    botsearch.push_back(make_pair(ty, tx));
    for(int x = 0; x < 24; x++)
      for(int t = 0; t < 24; t++)
	if(botmap[x][t] == -1)
	  botmap[x][t] = 0;
    botmap[y][x] = -1;
    do{
      pair<int, int> cr = botsearch[0];
      botsearch.pop_front();
      for(int j = 0; j < 4; j++){
	int sx = cr.second + dir[j][1], sy = cr.first + dir[j][0];
	if(botmap[sy][sx] == 0 && !isOut(sy, sx)){
	  //botsearch.push_back(make_pair(sy, sx));
	  bcount++;
	  botmap[sy][sx] = -1;
	  pmap[sy][sx].first = bcount;
	  pmap[sy][sx].second = 2;
	}
      } 
    }while(!botsearch.empty());
  }/*
  for(int f = 0; f < 24; f++){
    for(int e = 0; e < 24; e++)
      printf("%d ", pmap[f][e].second);
    printf("\n");
    }*/
  printf("\n");
/*
    //player's bfs
    tx = x2 + dir[i][0]; ty = y2 + dir[i][1];
    botsearch.push_back(make_pair(ty, tx));
    do{
      for(int j = 0; j < 4; j++){
	pair<int, int> cr = botsearch[0];
	botsearch.pop_front();
	int sx = cr.second + dir[j][1], sy = cr.first + dir[j][0];
	if(botmap[sy][sx] == -1 && isOut(sy, sx)){
	  pcount++;
	  if(pmap[sy][sx].first > pcount){
	    botsearch.push_back(make_pair(sy, sx));
	    botmap[sy][sx] = 0;
	    pmap[sy][sx].second = 1;
	  }
	}
      }
    }while(!botsearch.empty());
    
    for(int r = 0; r < 24; r++){
      for(int t = 0; t < 24; t++){
	if(pmap[r][t].second == 1)
	  ways[i][1]++;
	else if(pmap[r][t].second == 2) //bot ma dvojku, hrac 1
	  ways[i][0]++;
      }
    }
  }/*
  int result[4];
  result[0] = ways[0][0] - ways[0][1]; result[1] = ways[1][0] - ways[1][1];
  result[2] = ways[2][0] - ways[2][1]; result[3] = ways[3][0] - ways[3][1];
  int ans = 0;
  for(int i = 1; i < 4; i++){
    if(result[i] < result[ans])
      ans = i;
  }
  if(ans == 0) y--;
  else if(ans == 1) y++;
  else if(ans == 2) x--;
  else if(ans == 3) x++;*/
}
