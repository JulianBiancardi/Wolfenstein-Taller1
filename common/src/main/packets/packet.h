#ifndef PACKET_H
#define PACKET_H

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
  int type;  // 1 MOVE, 2 GRAB, 3 SHOT HIT, 4 DAMAGE, 5 CHANGE GUN, 6 SHOT MISS
  int player_id;
  union data {
    PointData point;  // MOVE
    int item;         // GRAB
    ShootData shot;   // SHOT HIT
    double damage;    // DAMAGE
    int gun;    // CHANGE GUN
    int bullets_shot; // SHOT MISS
  } data;
} __attribute__((packed)) packet_t;

#endif
