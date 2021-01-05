#include "key.h"

Key::Key(Point center, int id) : Items(center, id) {

}

void Key::use(Player &user) {

}

Items *Key::copy() {
  return new Key(center, id);
}

bool Key::can_be_used_by(Player &whom) {
  return true;
}

void Key::remove() {

}
