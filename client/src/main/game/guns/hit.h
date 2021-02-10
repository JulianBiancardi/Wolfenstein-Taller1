#ifndef HIT_H
#define HIT_H

class Hit {
 private:
  unsigned char gun_id;
  int object_id;
  int damage;
  bool shot;

 public:
  Hit(unsigned char gun_id, int object_id, int damage, bool shot);
  Hit(Hit&& other);
  Hit& operator=(Hit&& other);
  ~Hit();

  unsigned char get_gun_id();
  int get_object_id();
  int get_damage();
  bool is_shot();
};

#endif
