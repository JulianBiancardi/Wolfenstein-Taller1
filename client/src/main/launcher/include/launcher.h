#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <list>

#include "../../server.h"
#include "match.h"

class Launcher {
 private:
  Server* server;
  std::list<Match> matches;

  void request_matches();
  void receive_matches();
  unsigned char get_amount_of_matches();
  void receive_match();

 public:
  explicit Launcher(Server* server);

  void update_matches();
  std::list<Match> get_matches() const;

  ~Launcher();
};

#endif
