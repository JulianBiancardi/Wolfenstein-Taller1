#include "bot_thread.h"

BotThread::BotThread(CollisionChecker& collision_checker, Map& map,
                     unsigned int player_id,
                     BlockingQueue<Packet>& blocking_queue,
                     Match* match ) : Thread(), bot(collision_checker, map, player_id, blocking_queue, match){
//  this->bot = Bot(collision_checker, map, player_id, blocking_queue, match);
}

void BotThread::run() {
  //while (this->running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    this->bot.execute();
    this->bot.update_player();
  //}
}

BotThread::~BotThread() noexcept {

}