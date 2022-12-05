#pragma once

#include <boost/asio.hpp>
#include <functional>

using TimerProc=std::function<void(void *)>;
class CppTimer
{
private:
    static  boost::asio::io_service ioService; 
    boost::asio::deadline_timer dlTimer;
    uint interval;
    TimerProc timeoutProc;
public:
    CppTimer(TimerProc proc);
    ~CppTimer();
    void start();
    void stop();
};

CppTimer::CppTimer(TimerProc proc):dlTimer(ioService)
{
}

CppTimer::~CppTimer()
{
}

boost::asio::io_service  CppTimer::ioService;