#ifndef Player_h
#define Player_h
class Player{
 public:
  int x;
  int y;

  Player(int xcord, int ycord);
  bool isOut();
};
#endif // Player_h
