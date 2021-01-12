#ifndef PACKET_H
#define PACKET_H

typedef struct PointData {
  double x;
  double y;
} PointData;

typedef struct ShootData {
  double damage_done;  // May use float
  int enemy_shot;      // -1 if no enemy was shot
} ShootData;

typedef struct packet {
  int type;  // 1 MOVE, 2 GRAB, 3 SHOOT
  int player_id;
  union data {
    PointData point;  // MOVE
    int item;         // GRAB
    ShootData shot;   // SHOOT
  } data;
} __attribute__((packed)) packet_t;

#endif
