#ifndef PACKET_H
#define PACKET_H

// TODO Move to common space
typedef struct PointData {
  double x;
  double y;
} PointData;

typedef struct ShootData {
  int gun;
  double damage_done;  // May use float
  int enemy_shot;      // -1 if no enemy was shot
} PointData;

typedef struct packet {
  int type;  // 1 MOVE, 2 GRAB
  int player_id;
  union data {
    PointData point;  // MOVE
    int item;         // GRAB
    ShootData shot;   // SHOOT
  } data;
} __attribute__((packed)) packet_t;

#endif
