#include "protected_queue_tests.h"

#include <utility>
#include <vector>

#include "../../main/data_structures/protected_queue.h"
#include "../tests_setup.h"

int static empty_creation_test();
int static vector_creation_test();
int static enqueue_test();
int static dequeue_test();
int static front_test();
int static empty_test();

void protected_queue_tests() {
  begin_tests("PROTECTED QUEUE");

  print_test("La cola protegida se crea vacía", empty_creation_test, NO_ERROR);
  print_test("La cola protegida se crea correctamente con un vector",
             vector_creation_test, NO_ERROR);
  print_test("La cola protegida devuelve correctamente el siguiente elemento",
             front_test, NO_ERROR);
  print_test("La cola protegida encola correctamente", enqueue_test, NO_ERROR);
  print_test("La cola protegida desencola correctamente", dequeue_test,
             NO_ERROR);
  print_test("La cola protegida reporta correctamente estar vacía o no",
             empty_test, NO_ERROR);

  end_tests();
}

int static empty_creation_test() {
  ProtectedQueue<int> pq;
  if (!pq.empty()) {
    return ERROR;
  }
  return NO_ERROR;
}

int static vector_creation_test() {
  std::vector<int> v;
  v.push_back(5);
  v.push_back(1);
  ProtectedQueue<int> pq(v);
  return NO_ERROR;
}

int static front_test() {
  ProtectedQueue<int> pq;
  pq.enqueue(9);

  if (pq.front() != 9) {
    return ERROR;
  }

  pq.enqueue(5);

  if (pq.front() != 9) {
    return ERROR;
  }

  int buf;
  pq.dequeue(buf);

  if (pq.front() != 5) {
    return ERROR;
  }

  return NO_ERROR;
}

int static enqueue_test() {
  ProtectedQueue<int> pq;
  int num = 3;
  int num2 = 5;
  pq.enqueue(num);
  pq.enqueue(std::move(num2));
  return NO_ERROR;
}

int static dequeue_test() {
  ProtectedQueue<int> pq;
  int res;
  pq.enqueue(3);

  pq.dequeue(res);

  if (res != 3) {
    return ERROR;
  }
  return NO_ERROR;
}

int static empty_test() {
  ProtectedQueue<int> pq;
  if (!pq.empty()) {
    return ERROR;
  }

  pq.enqueue(5);
  if (pq.empty()) {
    return ERROR;
  }

  pq.enqueue(8);
  if (pq.empty()) {
    return ERROR;
  }

  int buf;
  pq.dequeue(buf);
  if (pq.empty()) {
    return ERROR;
  }

  pq.dequeue(buf);
  if (!pq.empty()) {
    return ERROR;
  }

  return NO_ERROR;
}