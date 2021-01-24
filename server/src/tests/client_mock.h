#ifndef WOLFENSTEIN_TALLER1_COMMON_TESTS_GAME_TEST_CLIENT_MOCK_H_
#define WOLFENSTEIN_TALLER1_COMMON_TESTS_GAME_TEST_CLIENT_MOCK_H_

#include "../main/game/collision_checker.h"

#define WALL 1  // TODO Remove this and ask in Config

Point next_position_up(const Point& position, const Angle& angle);
Point next_position_down(const Point& position, const Angle& angle);
Point next_position_right(const Point& position, const Angle& angle);
Point next_position_left(const Point& position, const Angle& angle);
Point next_position_up_right(const Point& position, const Angle& angle);
Point next_position_up_left(const Point& position, const Angle& angle);
Point next_position_down_right(const Point& position, const Angle& angle);
Point next_position_down_left(const Point& position, const Angle& angle);

void put_data(Matrix<int>& map_data);
void put_data_on_borders(Matrix<int>& map_data);

#endif //WOLFENSTEIN_TALLER1_COMMON_TESTS_GAME_TEST_CLIENT_MOCK_H_
