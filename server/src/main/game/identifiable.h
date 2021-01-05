#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_IDENTIFIABLE_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_IDENTIFIABLE_H_

class Identifiable {
 protected:
  int id;

 public:
  Identifiable(int id) : id(id) {}

  int get_id() { return id; }
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_IDENTIFIABLE_H_
