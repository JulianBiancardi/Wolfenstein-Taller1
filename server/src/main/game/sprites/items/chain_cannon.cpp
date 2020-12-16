#include "chain_cannon.h"
#include "../../guns/chain_cannon.h"

ChainCannon::ChainCannon(Point center) : Items(center) {

}

void ChainCannon::use(Player &user) {
  //user.add_gun(gun);
}

bool ChainCannon::can_be_used_by(Player &whom) {
  //return !whom.has_gun(gun);
  return false;
}

void ChainCannon::remove() {

}
