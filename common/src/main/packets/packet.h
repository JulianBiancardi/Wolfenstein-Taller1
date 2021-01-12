#ifndef PACKET_H
#define PACKET_H

// TODO Move to common space
typedef struct PointData {
  double x;
  double y;
} PointData;

typedef struct packet {
  int type;  // 1 MOVE, 2 GRAB
  int player_id;
  union data {
    PointData point;  // MOVE
    int item;         // GRAB
  } data;
} __attribute__((packed)) packet_t;

#endif
