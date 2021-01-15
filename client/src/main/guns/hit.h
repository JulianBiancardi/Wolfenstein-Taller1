#ifndef HIT_H
#define HIT_H

class Hit {
 private:
  int object_id;
  int damage;

 public:
  Hit(int object_id, int damage);
  Hit(Hit&& other);
  Hit& operator=(Hit&& other);
  ~Hit();

  int get_object_id();
  int get_damage();
};

#endif
