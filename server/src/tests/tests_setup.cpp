#include "tests_setup.h"

#include <iostream>

#define ERROR_RED "\x1b[31m"
#define CORRECT_GREEN "\x1b[32m"
#define RESET_FONT "\x1b[0m"
#define BOLD_FONT "\x1b[1m"

#define DIV_LEN 80
/* Todo remove this? std::cout causes problems in bot class. printf works.
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

*/


void print_test(std::string message, int (*func)(), int expected_value) {
  int test_result = func();

  printf("%s: ", message.c_str());
  if (test_result != expected_value) {
    printf("%sERROR%s\n", ERROR_RED, RESET_FONT);
    printf("\tExpected value: %i\n", expected_value);
    printf("\tInstead got: %i\n", test_result);
  } else {
    printf("%sOK%s\n", CORRECT_GREEN, RESET_FONT);
  }
}

void begin_tests(std::string module_tested) {
  for (int i = 0; i < DIV_LEN; i++) {
    printf("=");
  }
  printf("\n");

  for (size_t i = 1; i < (DIV_LEN - module_tested.length()) / 2; i++) {
    printf(" ");
  }
  printf("%s%s%s", BOLD_FONT, module_tested.c_str(), RESET_FONT);
  for (size_t i = 1; i < (DIV_LEN - module_tested.length()) / 2; i++) {
    printf(" ");
  }
  printf("\n\n");
}

void end_tests() { printf("\n"); }
