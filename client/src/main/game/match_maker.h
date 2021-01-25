#ifndef MATCH_MAKER_H
#define MATCH_MAKER_H

#include "casters/match_maker_caster.h"
#include "match.h"
#include "sdl/window.h"
#include "server.h"

class MatchMaker {
 private:
  Server& server;
  MatchMakerCaster caster;
  void handle_events();

 public:
  explicit MatchMaker(Server& server, Window& window);
  ~MatchMaker();

  Match join_match();
};

#endif
