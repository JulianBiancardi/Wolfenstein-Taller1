#include "food.h"

Food::Food(Point center) : Items(center) {
  health_recovered = 10;
}

void Food::use(Player &user) {
  user.add_health(health_recovered);
}

bool Food::can_be_used_by(Player &whom) {
  return true;
}

void Food::remove() {

}

