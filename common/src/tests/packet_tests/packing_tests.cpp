#include "packing_tests.h"

#include <cstring>

#include "../../main/packets/packing.h"
#include "../tests_setup.h"

int static c_test();
int static uc_test();
int static i_test();
int static ui_test();
int static l_test();
int static ul_test();
int static h_test();
int static uh_test();
int static s_test();

void packing_tests() {
  begin_tests("PACKING");

  print_test("A char is packed and unpacked successfully", c_test, NO_ERROR);
  print_test("An unsigned char is packed and unpacked succesfully", uc_test,
             NO_ERROR);
  print_test("An integer is packed and unpacked successfully", i_test,
             NO_ERROR);
  print_test("An unsigned integer is packed and unpacked successfully", ui_test,
             NO_ERROR);
  print_test("A long integer is packed and unpacked successfully", l_test,
             NO_ERROR);
  print_test("An unsigned long integer is packed and unpacked successfully",
             ul_test, NO_ERROR);
  print_test("A long long integer is packed and unpacked successfully", h_test,
             NO_ERROR);
  print_test(
      "An unsigned long long integer is packed and unpacked successfully",
      uh_test, NO_ERROR);
  print_test("A string is packed and unpacked successfully", s_test, NO_ERROR);

  end_tests();
}

int static c_test() {
  unsigned char buf[1];
  char a = -10;
  char b = 54;
  char c = 1;

  packi8(buf, a);
  if (unpacki8(buf) != a) {
    return ERROR;
  }

  packi8(buf, b);
  if (unpacki8(buf) != b) {
    return ERROR;
  }

  packi8(buf, c);
  if (unpacki8(buf) != c) {
    return ERROR;
  }

  char a_unpacked[1];
  pack(buf, "c", a);
  unpack(buf, "c", a_unpacked);
  if (a != *a_unpacked) {
    return ERROR;
  }

  char b_unpacked[1];
  pack(buf, "c", b);
  unpack(buf, "c", b_unpacked);
  if (b != *b_unpacked) {
    return ERROR;
  }

  char c_unpacked[1];
  pack(buf, "c", c);
  unpack(buf, "c", c_unpacked);
  if (c != *c_unpacked) {
    return ERROR;
  }

  return NO_ERROR;
}

int static uc_test() {
  unsigned char buf[4];
  unsigned char a = 9;
  unsigned char b = 100;
  unsigned char c = 0;

  packi8(buf, a);
  if (unpacku8(buf) != a) {
    return ERROR;
  }

  packi8(buf, b);
  if (unpacku8(buf) != b) {
    return ERROR;
  }

  packi8(buf, c);
  if (unpacku8(buf) != c) {
    return ERROR;
  }

  return NO_ERROR;
}

int static i_test() {
  unsigned char buf[2];
  int a = 0;
  int b = -1;
  int c = 69;
  int d = -1024;

  packi16(buf, a);
  if (unpacki16(buf) != a) {
    return ERROR;
  }

  packi16(buf, b);
  if (unpacki16(buf) != b) {
    return ERROR;
  }

  packi16(buf, c);
  if (unpacki16(buf) != c) {
    return ERROR;
  }

  packi16(buf, d);
  if (unpacki16(buf) != d) {
    return ERROR;
  }

  return NO_ERROR;
}

int static ui_test() {
  unsigned char buf[2];
  unsigned int a = 0;
  unsigned int b = 4800;
  unsigned int c = 10000;
  unsigned int d = 61789;

  packi16(buf, a);
  if (unpacku16(buf) != a) {
    return ERROR;
  }

  packi16(buf, b);
  if (unpacku16(buf) != b) {
    return ERROR;
  }

  packi16(buf, c);
  if (unpacku16(buf) != c) {
    return ERROR;
  }

  packi16(buf, d);
  if (unpacku16(buf) != d) {
    return ERROR;
  }

  return NO_ERROR;
}

int static l_test() {
  unsigned char buf[4];
  long int a = 0;
  long int b = -1;
  long int c = 12234912;
  long int d = -34122791;

  packi32(buf, a);
  if (unpacki32(buf) != a) {
    return ERROR;
  }

  packi32(buf, b);
  if (unpacki32(buf) != b) {
    return ERROR;
  }

  packi32(buf, c);
  if (unpacki32(buf) != c) {
    return ERROR;
  }

  packi32(buf, d);
  if (unpacki32(buf) != d) {
    return ERROR;
  }

  return NO_ERROR;
}

int static ul_test() {
  unsigned char buf[4];
  unsigned long int a = 0;
  unsigned long int b = 10101010;
  unsigned long int c = 123944912;
  unsigned long int d = 34123456;

  packi32(buf, a);
  if (unpacki32(buf) != a) {
    return ERROR;
  }

  packi32(buf, b);
  if (unpacki32(buf) != b) {
    return ERROR;
  }

  packi32(buf, c);
  if (unpacki32(buf) != c) {
    return ERROR;
  }

  packi32(buf, d);
  if (unpacki32(buf) != d) {
    return ERROR;
  }

  return NO_ERROR;
}

int static h_test() {
  unsigned char buf[8];
  long long int a = 0;
  long long int b = -1;
  long long int c = 12234912;
  long long int d = -347859122791;

  packi64(buf, a);
  if (unpacki64(buf) != a) {
    return ERROR;
  }

  packi64(buf, b);
  if (unpacki64(buf) != b) {
    return ERROR;
  }

  packi64(buf, c);
  if (unpacki64(buf) != c) {
    return ERROR;
  }

  packi64(buf, d);
  if (unpacki64(buf) != d) {
    return ERROR;
  }

  return NO_ERROR;
}

int static uh_test() {
  unsigned char buf[8];
  unsigned long long int a = 0;
  unsigned long long int b = 1;
  unsigned long long int c = 97252234912;
  unsigned long long int d = 3141592657859122791;

  packi64(buf, a);
  if (unpacki64(buf) != a) {
    return ERROR;
  }

  packi64(buf, b);
  if (unpacki64(buf) != b) {
    return ERROR;
  }

  packi64(buf, c);
  if (unpacki64(buf) != c) {
    return ERROR;
  }

  packi64(buf, d);
  if (unpacki64(buf) != d) {
    return ERROR;
  }

  return NO_ERROR;
}

int static s_test() {
  unsigned char buf[1024];
  const char* stringA = "H";
  const char* stringB = "Hello World!";
  const char* stringC =
      "Hello World! This is a test. The present string should be packed and "
      "unpacked successfully using my module.";

  char stringAunpacked[1024];
  char stringBunpacked[1024];
  char stringCunpacked[1024];

  size_t lenA = pack(buf, "s", stringA);
  if (lenA != strlen(stringA) + 2) {
    return ERROR;
  }
  unpack(buf, "s", stringAunpacked);
  if (strncmp(stringA, stringAunpacked, lenA) != 0) {
    return ERROR;
  }

  size_t lenB = pack(buf, "s", stringB);
  if (lenB != strlen(stringB) + 2) {
    return ERROR;
  }
  unpack(buf, "s", stringBunpacked);
  if (strncmp(stringB, stringBunpacked, lenB) != 0) {
    return ERROR;
  }

  size_t lenC = pack(buf, "s", stringC);
  if (lenC != strlen(stringC) + 2) {
    return ERROR;
  }
  unpack(buf, "s", stringCunpacked);
  if (strncmp(stringC, stringCunpacked, lenC) != 0) {
    return ERROR;
  }

  return NO_ERROR;
}
