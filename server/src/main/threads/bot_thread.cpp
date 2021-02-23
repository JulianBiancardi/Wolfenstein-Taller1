#include "bot_thread.h"
#include <syslog.h>

BotThread::BotThread(CollisionChecker& collision_checker, Map& map,
                     unsigned int player_id,
                     BlockingQueue<Packet>& blocking_queue,
                     Match* match ) : Thread(), bot
                     (collision_checker,map, player_id, blocking_queue,
                      match), running(true){
  for (int j = 0; j < map.get_rows(); j++) {
    for (int i = 0; i < map.get_columns(); i++) {
      bot.load_map(j,i,  map(j, i));
    }
  }
}
void BotThread::force_stop() {
  this->running = false;
}
void BotThread::run() {
  try{
    while (this->running){
      std::this_thread::sleep_for(std::chrono::milliseconds(40));
      this->bot.execute();
      this->bot.update_player();
      if (this->bot.is_dead()){
        this->force_stop();
        this->join();
      }
    }
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] BotThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] BotThread - Unknown error");
  }

}

BotThread::~BotThread() noexcept {

}