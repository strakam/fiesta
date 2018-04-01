#ifndef Player_h
#define Player_h
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
class Player{
 public:
  int x, y;
  int x2, y2;
  int dir [4][2];
  vector<vector<int> > botmap;

  Player(int ycord, int xcord);
  void inidirs();
  static bool isOut(int y, int x);
  void calculate();
};
#endif // Player_h
