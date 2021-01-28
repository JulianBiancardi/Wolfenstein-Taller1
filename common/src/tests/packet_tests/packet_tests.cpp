#include "packet_tests.h"

#include <cstring>

#include "../../main/packets/packet.h"
#include "../../main/packets/packing.h"
#include "../tests_setup.h"

int static creation_test();
int static size_test();
int static type_test();
int static data_test();

void packet_tests() {
  begin_tests("PACKET");

  print_test("El paquete se crea correctamente", creation_test, NO_ERROR);
  print_test("El paquete devuelve su tamaño correctamente", size_test,
             NO_ERROR);
  print_test("El paquete devuelve su tipo correctamente", type_test, NO_ERROR);
  print_test("El paquete devuelve su información correctamente", data_test,
             NO_ERROR);

  end_tests();
}

int static creation_test() {
  unsigned char packet1[1] = {19};
  Packet p1(1, packet1);

  unsigned char packet2[10];
  size_t packet2size = pack(packet2, "Iccc", 3, 'a', 'b', 'c');
  Packet p2(packet2size, packet2);

  unsigned char packet3[50];
  size_t packet3size = pack(packet3, "Is", 8, "Hello World!");
  Packet p3(packet3size, packet3);

  return NO_ERROR;
}

int static size_test() {
  unsigned char packet1[2] = {19, 20};
  Packet p1(2, packet1);
  if (p1.get_size() != 2) {
    return ERROR;
  }

  unsigned char packet2[10];
  size_t packet2size = pack(packet2, "Iccc", 3, 'a', 'b', 'c');
  Packet p2(packet2size, packet2);
  if (p2.get_size() != 5) {
    return ERROR;
  }

  unsigned char packet3[50];
  size_t packet3size = pack(packet3, "Is", 8, "Hello World!");
  Packet p3(packet3size, packet3);
  if (p3.get_size() != 16) {
    return ERROR;
  }

  return NO_ERROR;
}

int static type_test() {
  unsigned char packet1[2] = {19, 20};
  Packet p1(2, packet1);
  if (p1.get_type() != 19) {
    return ERROR;
  }

  unsigned char packet2[10];
  unsigned char type = {3};
  size_t packet2size = pack(packet2, "cccc", type, 'a', 'b', 'c');
  Packet p2(packet2size, packet2);
  if (p2.get_type() != type) {
    return ERROR;
  }

  unsigned char packet3[50];
  size_t packet3size = pack(packet3, "cs", 8, "Hello World!");
  Packet p3(packet3size, packet3);
  if (p3.get_type() != 8) {
    return ERROR;
  }

  return NO_ERROR;
}

int static data_test() {
  unsigned char packet1[2] = {19, 20};
  Packet p1(2, packet1);
  if (memcmp(packet1, p1.get_data(), 2) != 0) {
    return ERROR;
  }

  unsigned char packet2[10];
  size_t packet2size = pack(packet2, "Iccc", 3, 'a', 'b', 'c');
  Packet p2(packet2size, packet2);
  if (memcmp(packet2, p2.get_data(), packet2size) != 0) {
    return ERROR;
  }

  unsigned char packet3[50];
  size_t packet3size = pack(packet3, "Is", 8, "Hello World!");
  Packet p3(packet3size, packet3);
  if (memcmp(packet3, p3.get_data(), packet3size) != 0) {
    return ERROR;
  }

  return NO_ERROR;
}
