#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "match.h"
#include "server.h"

class Launcher {
 private:
  Server& server;
  std::vector<Match> matches;

  void update_matches();
  void request_matches();
  void receive_matches();
  unsigned char get_amount_of_matches();
  void receive_match();

 public:
  explicit Launcher(Server& server);
  ~Launcher();

  /* Run the launcher */
  Match operator()();
};

#endif
