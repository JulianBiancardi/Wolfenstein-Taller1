#include "blocking_queue_tests.h"

#include <utility>
#include <vector>

#include "../src/main/data_structures/blocking_queue.h"
#include "tests_setup.h"

int static empty_creation_test();
int static vector_creation_test();
int static enqueue_test();
int static dequeue_test();

void blocking_queue_tests() {
  begin_tests("BLOCKING QUEUE");

  print_test("La cola bloqueante se crea vacía correctamente",
             empty_creation_test, NO_ERROR);
  print_test("La cola bloqueante encola correctamente", enqueue_test, NO_ERROR);
  print_test("La cola bloqueante desencola correctamente", dequeue_test,
             NO_ERROR);

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