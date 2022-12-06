#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

class Timer {
 public:
  Timer() = delete;

  Timer(int period, std::function<void()> func)
      : _callFunc(func), _period(period), _timer(_ioc) {
    static std::once_flag flag;
    start();
    std::call_once(flag, [this] {this->startThread();});
  }

  ~Timer() {
    std::cout << "timer is stop." << std::endl;

    stop();
  };

  void start() {
    _timer.expires_from_now(boost::posix_time::milliseconds(_period));

    _timer.async_wait([this](auto e) { this->onTimer(e, this->_timer); });
  }

  void stop() {
    _callFunc = nullptr;

    _ioc.stop();
  };

  void setCallFunc(std::function<void()> func) { _callFunc = func; };

 private:
  void startThread() {
    for (int i = 0; i < 1; i++) {
      std::thread([&] { _ioc.run(); }).detach();
    }
  }
  std::function<void()> _callFunc;

  int _period;

  static boost::asio::io_context _ioc;

  boost::asio::deadline_timer _timer;

  void onTimer(const boost::system::error_code& e,
               boost::asio::deadline_timer& ptime) {
    if (e) {
      std::cout << "timer has some error:" << e.message()
                << ", error code:" << e.value() << std::endl;
     // return;
    }

    if (!_callFunc)

    {
      std::cout << "call function is null." << std::endl;

      return;
    }

    _callFunc();
    ptime.expires_from_now(boost::posix_time::milliseconds(_period));

    ptime.async_wait([this, &ptime](auto e) { this->onTimer(e, ptime); });
  }
};

boost::asio::io_context Timer::_ioc;