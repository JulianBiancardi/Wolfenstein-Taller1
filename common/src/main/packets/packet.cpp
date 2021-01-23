#include "packet.h"

#include <cstddef>
#include <cstring>

#include "packing.h"

Packet::Packet(size_t size, unsigned char* packet)
    : size(size), type(unpacku8(packet)), data(new unsigned char[size]) {
  memcpy(data, packet, size);
}

Packet::~Packet() { delete data; }

size_t Packet::get_size() { return size; }

unsigned char Packet::get_type() { return type; }

unsigned char* Packet::get_data() { return data; }