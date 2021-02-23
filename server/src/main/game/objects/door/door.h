#ifndef DOOR_H
#define DOOR_H

#include "../object.h"
#include "../player.h"

class Door : public Object, public Identifiable {
 protected:
  Door(const Point& center, unsigned int id);
  void change_state();

 public:
  /* Returns if the door state changed */
  virtual bool interact(Player& who) = 0;

  /* Returns if the door is open or not */
  bool is_open() const;

  /* Closes the door */
  void close();
};

class PairHasher {
 private:
 public:
  size_t operator()(const std::pair<unsigned int, unsigned int>& key) const {
    return (43 * key.first) % 1013 + (136 * key.second) % 1013;
  }
};

#endif
