#include "blocking_queue_tests.h"

#include <utility>

#include "../../main/data_structures/blocking_queue.h"
#include "../../main/packets/packet.h"
#include "../../main/packets/packing.h"
#include "../../main/threads/thread.h"
#include "../tests_setup.h"

int static empty_creation_test();
int static enqueue_test();
int static dequeue_test();
int static cv_test();

void blocking_queue_tests() {
  begin_tests("BLOCKING QUEUE");

  print_test("La cola bloqueante se crea vacía correctamente",
             empty_creation_test, NO_ERROR);
  print_test("La cola bloqueante encola correctamente", enqueue_test, NO_ERROR);
  print_test("La cola bloqueante desencola correctamente", dequeue_test,
             NO_ERROR);
  print_test(
      "La cola bloqueante es notificada correctamente cuando se encola algo, "
      "destrabandose",
      cv_test, NO_ERROR);

  end_tests();
}

int static empty_creation_test() {
  BlockingQueue<int> bq;
  return NO_ERROR;
}

int static enqueue_test() {
  BlockingQueue<int> bq;
  int num = 3;
  int num2 = 5;
  bq.enqueue(num);
  bq.enqueue(std::move(num2));
  return NO_ERROR;
}

int static dequeue_test() {
  BlockingQueue<int> bq;
  int res;
  bq.enqueue(3);

  bq.dequeue(res);

  if (res != 3) {
    return ERROR;
  }
  return NO_ERROR;
}

class TestThreadEnqueue : public Thread {
 private:
  BlockingQueue<int>& queue;
  BlockingQueue<Packet>& queue2;
  int result;
  void run() {
    unsigned char data[5];
    size_t size = pack(data, "C", 2);
    Packet packet(size, data);
    queue2.enqueue(packet);
  }

 public:
  TestThreadEnqueue(BlockingQueue<int>& queue, BlockingQueue<Packet>& queue2)
      : queue(queue), queue2(queue2) {}
  ~TestThreadEnqueue() {}
};

class TestThreadDequeue : public Thread {
 private:
  BlockingQueue<int>& queue;
  BlockingQueue<Packet>& queue2;
  Packet result;
  void run() {
    Packet a;
    queue2.dequeue(a);
    result = a;
  }

 public:
  TestThreadDequeue(BlockingQueue<int>& queue, BlockingQueue<Packet>& queue2)
      : queue(queue), queue2(queue2) {}
  ~TestThreadDequeue() {}
  Packet& get_result() { return result; }
};

int static cv_test() {
  BlockingQueue<int> q1;
  BlockingQueue<Packet> q2;
  TestThreadEnqueue t1(q1, q2);
  TestThreadDequeue t2(q1, q2);
  t2.start();
  t1.start();
  Packet& result = t2.get_result();
  t1.join();
  t2.join();
  if (result.get_type() != 2) {
    return ERROR;
  }
  return NO_ERROR;
}
