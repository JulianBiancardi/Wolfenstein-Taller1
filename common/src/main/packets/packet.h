#ifndef PACKET_H
#define PACKET_H

#include <cstddef>

#include "../ids/packet_ids.h"

class Packet {
 private:
  size_t size;
  unsigned char type;
  unsigned char* data;

 public:
  Packet();
  explicit Packet(size_t size, unsigned char* packet);

  Packet(const Packet& other);
  Packet& operator=(const Packet&);

  Packet(Packet&& other);
  Packet& operator=(Packet&& other);

  ~Packet();

  /* Returns the size of the packet */
  size_t get_size();

  /* Returns the type of the packet */
  unsigned char get_type();

  /* Returns the data of the packet */
  unsigned char* get_data();
};

#endif
