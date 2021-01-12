#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_H_

typedef struct PointData {
  double x;
  double y;
} PointData;

typedef struct ShootData {
  int gun;
  double damage_done; // May use float
  int enemy_shot; // -1 if no enemy was shot
} PointData;

typedef struct Event {
  int type; // 1 MOVE, 2 GRAB, 3 SHOOT
  int player_id;
  union data {
    PointData point; // MOVE
    int item; // GRAB
    ShootData shot; // SHOOT
  } data;
} Event;

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_H_
