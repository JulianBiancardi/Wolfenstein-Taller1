#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_H_

// TODO Move to common space
typedef struct PointData {
  double x;
  double y;
} PointData;

typedef struct Event {
  int type; // 1 MOVE, 2 GRAB
  int player_id;
  union data {
    PointData point; // MOVE
    int item; // GRAB
  } data;
} Event;

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_H_
