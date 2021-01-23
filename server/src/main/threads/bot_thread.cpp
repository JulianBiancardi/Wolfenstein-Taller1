#include "bot_thread.h"

BotThread::BotThread(Bot &bot) : Thread(), bot(bot) {}

void BotThread::run() {
  while (this->running) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //this->bot.execute();
  }
}

BotThread::~BotThread() noexcept {

}