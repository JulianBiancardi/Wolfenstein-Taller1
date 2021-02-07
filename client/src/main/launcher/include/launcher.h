#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <list>

#include "../../server.h"
#include "match.h"

class Launcher {
 private:
  Server* server;
  std::list<Match> matches;

  /* Used for updating matches */
  void request_matches();
  void receive_matches();
  unsigned char get_amount_of_matches();
  void receive_match();

  /* Used for creating matches */
  void request_new_match(const std::string& map_name);

  /* Used for joining a match */
  void request_join_match(unsigned char match_id);
  unsigned char receive_join_match_result();

 public:
  explicit Launcher(Server* server);

  std::list<Match> get_matches() const;
  std::list<Match> get_maps() const;

  /* Requests the server for an update on the matches.
   * Clears the matches and fills it with the updated data.
   */
  void update_matches();

  /* Receives a map_name and requests the server to create a match.
   * Returns a match_id associated to the new match,
   * or 0 if the server failed to create a new match.
   */
  unsigned char create_match(const std::string& map_name);

  /* Receives a match_id and requests the server to join the given match.
   * Returns the match_id if the server accepts the client joining,
   * or 0 if the server declines the client joining.
   */
  unsigned char join_match(unsigned char match_id);

  ~Launcher();
};

#endif
