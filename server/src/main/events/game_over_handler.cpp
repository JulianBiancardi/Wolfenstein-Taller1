#include "game_over_handler.h"
#include "../game/match.h"

GameOverHandler::GameOverHandler() {}

void GameOverHandler::handle(Match& match, CollisionChecker& checker) {
  match.end();
}
