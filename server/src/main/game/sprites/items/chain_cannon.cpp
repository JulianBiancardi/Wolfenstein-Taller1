#include "chain_cannon.h"
#include "../../guns/chain_cannon.h"

ChainCannon::ChainCannon(Point center, int id) : Items(center, id) {

}

void ChainCannon::use(Player &user) {
  //user.add_gun(gun);
}

Items *ChainCannon::copy() {
  return new ChainCannon(center, id);
}

bool ChainCannon::can_be_used_by(Player &whom) {
  //return !whom.has_gun(gun);
  return false;
}

void ChainCannon::remove() {

}
