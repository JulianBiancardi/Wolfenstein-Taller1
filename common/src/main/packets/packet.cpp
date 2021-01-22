#include "packet.h"

#include <cstddef>
#include <cstring>

#include "packing.h"

Packet::Packet(size_t size, unsigned char* packet)
    : size(size), type(unpacku8(packet)), packet(new unsigned char[size]) {
  memcpy(this->packet, packet, size);
}

Packet::~Packet() { delete packet; }

unsigned char* Packet::get_packet() { return packet; }

unsigned char Packet::get_type() { return type; }