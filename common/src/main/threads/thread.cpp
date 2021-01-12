#include "thread.h"

Thread::Thread() {}

Thread::~Thread() {}

void Thread::start() { thread = std::thread(&Thread::run, this); }

void Thread::join() { this->thread.join(); }
