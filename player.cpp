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
  deque<vector<int> > botsearch;
  int botbfs[24][24];
  int ways[4];
  int ans[4];
  for(int i = 0; i < 4; i++){
    ways[i] = -1000;
    ans[i] = -1000;
  }
  //bot's bfs
  for(int i = 0; i < 4; i++){ //vyber smerov bota
    for(int t = 0; t < 24; t++)
      for(int r = 0; r < 24; r++){
	botbfs[t][r] = botmap[t][r];
	if(botbfs[t][r] == 1)
	  botbfs[t][r] = -1;
	else if(botbfs[t][r] == 2)
	  botbfs[t][r] = -2;
      }
    int y1 = y + dir[i][0], x1 = x + dir[i][1];
    if(!isOut(y1, x1) && botbfs[y1][x1] == 0){ //prvy smer
      botbfs[y1][x1] = 1;
      vector<int> info;
      info.push_back(y1); info.push_back(x1); info.push_back(1);
      botsearch.push_back(info);
      
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
      }// tu konci bfs bota
      
      int pbfs[24][24];
      for(int g = 0; g < 4; g++){ //vyber smerov hraca
	for(int t = 0; t < 24; t++)
	  for(int r = 0; r < 24; r++){
	    pbfs[t][r] = botmap[t][r];
	    if(pbfs[t][r] == 1)
	      pbfs[t][r] = -1;
	    else if(pbfs[t][r] == 2)
	      pbfs[t][r] = -2;
	  }
	int yp = y2 + dir[g][0], xp = x2 + dir[g][1];
	if(!isOut(yp, xp) && pbfs[yp][xp] == 0){ //jeden smer hraca
	  pbfs[yp][xp] = 1;
	  vector<int> info;
	  info.push_back(yp); info.push_back(xp); info.push_back(1);
	  botsearch.push_back(info);
	  
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
	  ways[g] = 0;
	  for(int j = 0; j < 24; j++){
	    for(int k = 0; k < 24; k++){
	      if(botbfs[j][k] == 0){
		botbfs[j][k] = 100;
	      }
	      if(pbfs[j][k] == 0){
		pbfs[j][k] = 100;
	      }
	      if(botmap[j][k] == 0){
		if(botbfs[j][k] >= pbfs[j][k])
		  ways[g]--;
		else ways[g]++;
	      }
	    }
	  }
	  for(int m = 0; m < 24; m++){
	    for(int n = 0; n < 24; n++){
	      if(botbfs[m][n] == -2)
		printf("B ");
	      else if(botbfs[m][n] == -1)
		printf("H ");
	      else{
		if(botbfs[m][n] == 100)
		  printf("X ");
		else if(botbfs[m][n] > 9 && botbfs[m][n] < 100)
		  printf(". ");
		else
		  printf("%d ", botbfs[m][n]);
	      }
	    
	    }
	    printf("\n");
	  }
	  printf("\n");
	}// tu konci if (jeden smer hraca)
      }// tu koncia smery hraca
      int maxi = 0;
      for(int q = 0; q < 4; q++){
	if(ways[q] > ways[maxi]) maxi = q;
      }
      ans[i] = ways[maxi];
      for(int q = 0; q < 4; q++)
	ways[q] = -1000;
    }// tu konci if (smer bota)
  }
  int answer = 0;
  for(int h = 0; h < 4; h++)
    if(ans[h] > ans[answer]) answer = h;
  if(answer == 0) y--;
  else if(answer == 1) y++;
  else if(answer == 2) x--;
  else if(answer == 3) x++;
}
