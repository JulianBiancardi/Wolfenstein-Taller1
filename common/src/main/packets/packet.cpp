#include "packet.h"

#include <cstddef>
#include <cstring>

#include "packing.h"

Packet::Packet() : size(0), type(0), data(nullptr) {}

Packet::Packet(size_t size, unsigned char* packet)
    : size(size), type(unpacku8(packet)), data(new unsigned char[size]) {
  memcpy(data, packet, size);
}

Packet::Packet(Packet&& other) {
  this->size = other.size;
  this->type = other.type;
  this->data = other.data;

  other.size = 0;
  other.type = 0;
  other.data = nullptr;
}

Packet& Packet::operator=(Packet&& other) {
  if (this == &other) {
    return *this;
  }

  this->size = other.size;
  this->type = other.type;
  this->data = other.data;

  other.size = 0;
  other.type = 0;
  other.data = nullptr;

  return *this;
}

Packet::~Packet() {
  if (data != nullptr) {
    delete[] data;
  }
}

size_t Packet::get_size() { return size; }

unsigned char Packet::get_type() { return type; }

unsigned char* Packet::get_data() { return data; }