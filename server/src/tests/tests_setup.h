#ifndef TESTS_SETUP_H
#define TESTS_SETUP_H

#include <string>

#define NO_ERROR 0
#define ERROR -1

void print_test(std::string message, int (*func)(), int expected_value);
void begin_tests(std::string module_tested);
void end_tests();

#endif
