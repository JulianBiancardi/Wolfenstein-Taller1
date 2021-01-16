#ifndef PACKET_H
#define PACKET_H

// Packets type:
#define MOVE_PACKET 1
#define GRAB_PACKET 2
#define SHOT_HIT_PACKET 3
#define SHOT_MISS_PACKET 4
#define DAMAGE_PACKET 5
#define CHANGE_GUN_PACKET 6
#define KILL_PACKET 7
#define RESPAWNED_PACKET 8 // Used to solve bug (ask me which)

typedef struct PointData {
  double x;
  double y;
} PointData;

typedef struct ShootData {
  double damage_done;  // May use float
  int enemy_shot;
  int bullets_shot;
} ShootData;

typedef struct packet {
  int type;
  int player_id;
  union data {
    PointData point;  // MOVE
    int item;         // GRAB
    ShootData shot;   // SHOT HIT
    double damage;    // DAMAGE
    int gun;    // CHANGE GUN
    int bullets_shot; // SHOT MISS
    int killer; // KILL
  } data;
} __attribute__((packed)) packet_t;

#endif
