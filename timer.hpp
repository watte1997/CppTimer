#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <functional>
#include <mutex>

using TimerProc = std::function<void()>;
class CppTimer {
 private:
  enum class TimerStatus { Default, Running, Stop };
  static boost::asio::io_service ioService;
  static boost::thread_group threadpool;
  static std::once_flag flag;
  boost::asio::deadline_timer dlTimer;
  uint interval;
  TimerProc timeoutProc;
  TimerStatus timerStatus;

  void setTimeoutProc(TimerProc proc) { timeoutProc = proc; }
  void timeout()
  {
        
  }
 public:
  CppTimer(TimerProc proc)
      : dlTimer(ioService),
        timerStatus(TimerStatus::Default),
        timeoutProc(proc) {
    //           threadpool.create_thread(
    //   boost::bind(&boost::asio::io_service::run, &ioService));
    std::call_once(flag, [&] {
      threadpool.create_thread([&] { ioService.run(); });
      threadpool.create_thread([&] { ioService.run(); });
    });
  }

  ~CppTimer() { stop(); };

  void start(uint32_t msExpired) {
    if (msExpired == 0) return;

    dlTimer.expires_from_now(boost::posix_time::milliseconds(msExpired));
    dlTimer.async_wait([=](const boost::system::error_code &ec) {
      timeoutProc();
    });
    timerStatus = TimerStatus::Running;
  }

  void stop() {
    if (timerStatus == TimerStatus::Running) {
      dlTimer.cancel();
    }
    timerStatus = TimerStatus::Stop;
  };

  static void singleShot(TimerProc proc, uint32_t msExpired) {
    if (!proc || msExpired == 0) {
      return;
    }
    auto timer = new CppTimer([&] {});
    timer->setTimeoutProc([timer, proc] {
      proc();
      timer->stop();
      delete timer;
    });
    timer->start(msExpired);
  }
};

boost::asio::io_service CppTimer::ioService;
boost::thread_group CppTimer::threadpool;
std::once_flag CppTimer::flag;