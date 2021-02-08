#ifndef HIT_H
#define HIT_H

class Hit {
 private:
  int object_id;
  int damage;
  bool shot;

 public:
  Hit(int object_id, int damage, bool shot);
  Hit(Hit&& other);
  Hit& operator=(Hit&& other);
  ~Hit();

  int get_object_id();
  int get_damage();
  bool is_shot();
};

#endif
