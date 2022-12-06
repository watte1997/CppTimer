#include "timer.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

int i=0;
void timeout()
{
    printf("timeout\n");
    i++;
}
int main()
{
    printf("running2\n");
    auto timer=new CppTimer(timeout);
     std::cout<<"running1\n";
    timer->start(5000);
    timeout();
    while (true)
    {
        printf("running%d\n",i);
        sleep(2);
    }
}