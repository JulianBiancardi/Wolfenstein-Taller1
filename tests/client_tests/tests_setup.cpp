#include "tests_setup.h"

#include <iostream>

#define ERROR_RED "\x1b[31m"
#define CORRECT_GREEN "\x1b[32m"
#define RESET_FONT "\x1b[0m"
#define BOLD_FONT "\x1b[1m"

#define DIV_LEN 80

void print_test(std::string message, int (*func)(), int expected_value) {
  int test_result = func();

  std::cout << message << ": ";
  if (test_result != expected_value) {
    std::cout << ERROR_RED << "ERROR" << RESET_FONT << std::endl;
    std::cout << "\tExpected value: " << expected_value << "\n";
    std::cout << "\tInstead got: " << test_result << std::endl;
  } else {
    std::cout << CORRECT_GREEN << "OK" << RESET_FONT << std::endl;
  }
}

void begin_tests(std::string module_tested) {
  for (int i = 0; i < DIV_LEN; i++) {
    std::cout << '=';
  }
  std::cout << '\n';

  for (size_t i = 1; i < (DIV_LEN - module_tested.length()) / 2; i++) {
    std::cout << ' ';
  }
  std::cout << BOLD_FONT << module_tested << RESET_FONT;
  for (size_t i = 1; i < (DIV_LEN - module_tested.length()) / 2; i++) {
    std::cout << ' ';
  }
  std::cout << '\n' << std::endl;
}
void end_tests() { std::cout << "\n"; }
