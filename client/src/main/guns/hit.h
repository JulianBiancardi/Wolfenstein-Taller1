#ifndef HIT_H
#define HIT_H

class Hit {
 private:
  int object_id;
  int damage;
  int bullets_used;

 public:
  Hit(int object_id, int damage, int bullets_used);
  Hit(Hit&& other);
  Hit& operator=(Hit&& other);
  ~Hit();

  int get_object_id();
  int get_damage();
  int get_bullets_used();
};

#endif
