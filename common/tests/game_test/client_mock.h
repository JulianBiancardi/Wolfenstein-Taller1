#ifndef WOLFENSTEIN_TALLER1_COMMON_TESTS_GAME_TEST_CLIENT_MOCK_H_
#define WOLFENSTEIN_TALLER1_COMMON_TESTS_GAME_TEST_CLIENT_MOCK_H_

#include "../../../server/src/main/game/collision_checker.h"

Point next_position_up(Ray angled_position);
Point next_position_down(Ray angled_position);
Point next_position_right(Ray angled_position);
Point next_position_left(Ray angled_position);
Point next_position_up_right(Ray angled_position);
Point next_position_up_left(Ray angled_position);
Point next_position_down_right(Ray angled_position);
Point next_position_down_left(Ray angled_position);

void put_data(Matrix<int> &map_data);

#endif //WOLFENSTEIN_TALLER1_COMMON_TESTS_GAME_TEST_CLIENT_MOCK_H_
