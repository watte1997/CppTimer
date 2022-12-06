#include "timer.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

int i=0;
void timeout()
{
    printf("timeout\n");
    i++;
}
int main()
{
    boost::asio::io_context ioc;
  //  std::vector<Timer> tarr;

        auto t=new Timer(3000,timeout);
        t->start();
   // }

    // for (int i = 0; i < 3; ++i)
    //   {
    //     std::thread([&ioc]{ioc.run();}).detach();
    //   }
    // wait for all threads to be created
 //   timer->start();
    // std::thread t([&]{threads.join_all();}); 
    // t.detach();
    while (1)
    {
        sleep(2);
    }
    
}