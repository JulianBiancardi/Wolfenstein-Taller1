#ifndef PACKET_H
#define PACKET_H

#include <cstddef>

#include "../ids/packet_ids.h"

/*
#define MOVE_PACKET 1
#define GRAB_PACKET 2
#define SHOT_HIT_PACKET 3
#define SHOT_MISS_PACKET 4
#define DAMAGE_PACKET 5
#define CHANGE_GUN_PACKET 6
#define KILL_PACKET 7
#define RESPAWNED_PACKET 8  // Used to solve bug (ask me which)
#define GAME_OVER_PACKET 9
#define INVALID_ID -1
*/

// Packets type:
/*
#define MOVE_PACKET 1
#define ROTATE_PACKET 2
#define GRAB_PACKET 3
#define DOOR_PACKET 4
#define CHANGE_GUN_PACKET 5
#define DAMAGE_PACKET 6
#define GAME_OVER_PACKET 7
#define GRAB 5  // Player grabbed an item
#define GRAB_SIZE 6
*/

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
