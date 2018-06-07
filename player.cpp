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

int Player::dfs(int m, int ty, int tx){
   vector<vector<int> > ans;
   ans.resize(4);
   for(int i = 0; i < 4; i++)
     ans[i].push_back(-8000);
   if(m == 2){ //ak sme v tretom tahu, vypocitame ho
     botmap[ty][tx] = 2;
     cx = tx; cy = ty;
     int anss = pdfs(1, y2, x2);
     botmap[ty][tx] = 0;
     return anss; // hodnota tretieho tahu
   }
   else{ // ak niesme v tretom tahu tak prejdeme vsetky moznosti
     for(int i = 0; i < 4; i++){
       int y1 = ty + dir[i][0]; int x1 = tx + dir[i][1];
       if(!isOut(y1, x1) && botmap[y1][x1] == 0){
 	botmap[ty][tx] = 2;
 	ans[i][0] = dfs(m+1, y1, x1);
 	botmap[ty][tx] = 0;
       }
     }
     // vyber najlepsieho tahu aktualnej cesty
     if(m == 1){
       int t = 0;
       for(int j = 0; j < 4; j++)
	 if(ans[j][0] > ans[t][0]) t = j;
       
       if(t == 0) y--;
       else if(t == 1) y++;
       else if(t == 2) x--;
       else x++;
     }
   }  
}

// v podstate to iste ako bot dfs len ine :D 
int Player::pdfs(int m, int ty, int tx){
  vector<int> ans;
  if(m == 2){
    botmap[ty][tx] = 1;
    int anss = calculate(ty, tx, cy, cx);
    botmap[ty][tx] = 0;
    return anss;
  }
  else{
    for(int i = 0; i < 4; i++){
      int y1 = ty + dir[i][0]; int x1 = tx + dir[i][1];
      if(!isOut(y1, x1) && botmap[y1][x1] == 0){
	botmap[ty][tx] = 1;
	ans.push_back(pdfs(m+1, y1, x1));
	botmap[ty][tx] = 0;
      }
    }
    int mini = 9999;
    for(int i = 0; i < ans.size(); i++)
      if (ans[i] <  mini) mini = ans[i];
    return mini;
  }
}

void Player::sickmove(){
  dfs(1, y, x);
}

int Player::calculate(int ty, int tx, int cy, int cx){
  deque<vector<int> > botsearch;
  int botbfs[24][24];
  //bot's bfs
  for(int t = 0; t < 24; t++)
    for(int r = 0; r < 24; r++){
      botbfs[t][r] = botmap[t][r];
      if(botbfs[t][r] == 1)
	botbfs[t][r] = -1;
      else if(botbfs[t][r] == 2)
	botbfs[t][r] = -2;
    }
  vector<int> info;
  info.push_back(cy); info.push_back(cx); info.push_back(1);
  botsearch.push_back(info);
  // BFS BOT
  while(!botsearch.empty()){ //bfs 0
    vector<int> temp = botsearch[0];
    botsearch.pop_front();
    for(int j = 0; j < 4; j++){
      int sy = temp[0] + dir[j][0], sx = temp[1] + dir[j][1];
      if(!isOut(sy, sx) && botbfs[sy][sx] == 0){	  
	botbfs[sy][sx] = temp[2] + 1;
	vector<int> info;
	info.push_back(sy); info.push_back(sx); info.push_back(temp[2] + 1);
	botsearch.push_back(info);
      }
    }
  }
  //KONIEC BFS BOT
  int pbfs[24][24];
  for(int t = 0; t < 24; t++)
    for(int r = 0; r < 24; r++){
      pbfs[t][r] = botmap[t][r];
      if(pbfs[t][r] == 1)
	pbfs[t][r] = -1;
      else if(pbfs[t][r] == 2)
	pbfs[t][r] = -2;
    }
  info.clear();
  info.push_back(ty); info.push_back(tx); info.push_back(1);
  botsearch.push_back(info);
  //HRAC BFS
  while(!botsearch.empty()){
    vector<int> temp = botsearch[0];
    botsearch.pop_front();
    for(int j = 0; j < 4; j++){
      int sy = temp[0] + dir[j][0], sx = temp[1] + dir[j][1];
      if(!isOut(sy, sx) && pbfs[sy][sx] == 0){
	pbfs[sy][sx] = temp[2] + 1;
	vector<int> info;
	info.push_back(sy); info.push_back(sx); info.push_back(temp[2] + 1);
	botsearch.push_back(info);
      }
    }
  }//tu konci bfs hraca
  int botans = 0;
  for(int j = 0; j < 24; j++){
    for(int k = 0; k < 24; k++){
      if(botbfs[j][k] == 0){
	botbfs[j][k] = 1000;
      }
      if(pbfs[j][k] == 0){
	pbfs[j][k] = 1000;
      }
      if(botmap[j][k] == 0){
	if(botbfs[j][k] >= pbfs[j][k])
	  botans--;
	else botans++;
      }
    }
  }
  return botans;
}
