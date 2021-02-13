#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_THREADS_BOT_THREAD_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_THREADS_BOT_THREAD_H_

#include "../../../../common/src/main/threads/thread.h"
#include "../bot/bot.h"
class BotThread: public Thread {
 private:
  Bot bot;
  bool running;

 public:
  BotThread(CollisionChecker& collision_checker, Map& map,
            unsigned int player_id,
            BlockingQueue<Packet>& blocking_queue,
            Match* match );
  ~BotThread();
  void run() override;
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_THREADS_BOT_THREAD_H_
