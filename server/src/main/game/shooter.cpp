#include "shooter.h"

Shooter::Shooter(Point origin, double angle) :
    angled_position(origin, angle) {}

void Shooter::shoot(Gun &gun) {
  Randomizer<float> randomizer;
  float random_angle =
      randomizer.operator()(angled_position.get_angle() - M_PI / 12,
                            angled_position.get_angle() + M_PI / 12);

  Ray ray_cone(angled_position.get_origin(), M_PI / 2 + random_angle);

  bool y_intersection;
  //Point intersection = RayCasting::get_intersection(map, ray_cone,
  //                                                y_intersection);
  /*std::cout << "(" << intersection.getX();
std::cout << "; " << intersection.getY()<<")";*/

  /*this->shoot_player(thisse suicida por ahora, gun);*/
}
void Shooter::shoot_player(Player &shot_player, Gun &gun) {

}
