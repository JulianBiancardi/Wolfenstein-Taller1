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

// Gun type:
#define KNIFE_ID 1
#define PISTOL_ID 2
#define MACHINE_GUN_ID 3
#define CHAIN_CANNON_ID 4
#define ROCKET_LAUNCHER_ID 5

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
