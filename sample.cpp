#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "timer.hpp"

int i = 0;
void timeout1() { printf("timeout, thread id %d\n",std::this_thread::get_id()); }

void timeout2() { printf("timeout 2\n"); }

int main() {
  boost::asio::io_context ioc;
  //   auto t1 = new CppTimer(2000, timeout1);
  //   t1->start();

  //    auto t2 = new CppTimer(2000, timeout2);
  //   t2->start();

  for (int i = 0; i < 8; i++) {
        auto t1 = new CppTimer(2000, timeout1);
        t1->start();
  }
  while (1) {
    sleep(2);
  }
}