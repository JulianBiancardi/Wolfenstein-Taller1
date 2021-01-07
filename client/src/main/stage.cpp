#include "stage.h"
Stage::Stage() {}

void Stage::setPlayerPosition(int id, PointData point_data) {
  players.at(id).set_position(point_data);
}

void Stage::setPlayerHealth(int id, int health) {}

void Stage::addItem(int type, PointData point_data) {}

void Stage::removeItem(PointData point_data) {}

void Stage::removePlayer(int id) {}