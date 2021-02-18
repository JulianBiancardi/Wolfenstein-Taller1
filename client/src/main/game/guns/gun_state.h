#ifndef GUN_STATE_H
#define GUN_STATE_H

enum gun_state { ready, aim, shoot };

class GunState {
 private:
  gun_state state;
  int frame_count;

 public:
  GunState();
  ~GunState();
  void update(bool trigger);
};

#endif
