#ifndef Player_h
#define Player_h
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
class Player{
 public:
  int x, y, cx, cy;
  int x2, y2, cx2, cy2;
  int dir [4][2];
  vector<vector<int> > botmap;

  Player(int ycord, int xcord);
  void inidirs();
  static bool isOut(int y, int x);
  int calculate(int ty, int tx, int cy, int cx);
  void sickmove();
  int dfs(int m, int ty, int tx);
  int pdfs(int m, int ty, int tx);
};
#endif // Player_h
