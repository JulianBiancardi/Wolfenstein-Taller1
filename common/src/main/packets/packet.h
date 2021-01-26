#ifndef PACKET_H
#define PACKET_H

#include <cstddef>

#define SIZE_SIZE 2

// Packet types
#define END_OF_CONNECTION 0  // To end the connection
#define END_OF_CONNECTION_SIZE 3

#define START_OF_CONNECTION 1  // To notify the client his ID
#define START_OF_CONNECTION_SIZE 3

#define REQUEST_MATCHES 2

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

// Packets type:
#define MOVE_PACKET 1
#define ROTATE_PACKET 2
#define GRAB_PACKET 3
#define DOOR_PACKET 4
#define CHANGE_GUN_PACKET 5
#define DAMAGE_PACKET 6
#define GAME_OVER_PACKET 7

// TODO Move this somewhere else

// Moving directions:
#define INVALID 0
#define UP 1
#define UP_LEFT 2
#define LEFT 3
#define DOWN_LEFT 4
#define DOWN 5
#define DOWN_RIGHT 6
#define RIGHT 7
#define UP_RIGHT 8

// Rotating directions:
#define RIGHT_ROTATION 1
#define LEFT_ROTATION 2

// Gun type:
#define KNIFE_ID 1
#define PISTOL_ID 2
#define MACHINE_GUN_ID 3
#define CHAIN_CANNON_ID 4
#define ROCKET_LAUNCHER_ID 5

class Packet {
 private:
  size_t size;
  unsigned char type;
  unsigned char* data;

 public:
  Packet();
  explicit Packet(size_t size, unsigned char* packet);
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
