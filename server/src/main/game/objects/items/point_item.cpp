#include "point_item.h"

PointItem::PointItem(const Point& center, unsigned int id, int points_given)
    : Item(center, id), points_given(points_given) {}

void PointItem::use(Player& user) { user.add_points(points_given); }

bool PointItem::can_be_used_by(const Player& whom) { return true; }
