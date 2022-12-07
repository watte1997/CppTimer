#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

class CppTimer {
 public:
  CppTimer() = delete;

  CppTimer(int period, std::function<void()> func)
      : _callFunc(func), _period(period), _timer(_ioc) {}

  ~CppTimer() {
    stop();
  };

  void start() {
    _timer.expires_from_now(boost::posix_time::milliseconds(_period));

    _timer.async_wait([this](auto e) { this->onTimer(e, this->_timer); });

    std::call_once(flag, [this] { this->startThread(); });
  }

  void stop() {
    _callFunc = nullptr;

    _ioc.stop();
  };

  void setCallFunc(std::function<void()> func) { _callFunc = func; };

 private:
  std::function<void()> _callFunc;
  int _period;
  boost::asio::deadline_timer _timer;
  static boost::asio::io_context _ioc;
  static std::once_flag flag;

  void startThread() {
    for (int i = 0; i < 3; i++) {
      std::thread([&] { _ioc.run(); }).detach();
    }
  }

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

boost::asio::io_context CppTimer::_ioc;
std::once_flag CppTimer::flag;