#ifndef CONSTANT_RATE_H
#define CONSTANT_RATE_H

#include <functional>
#include <chrono>
#include <thread>
#include <cmath>

class ConstantRateLooper {
  private:
    double iter_per_sec;
    const std::function<bool(int)> func;
    int iter;
  public:
    explicit ConstantRateLooper(double rate, const std::function<bool(int)> func): iter_per_sec(rate), func(func), iter(0) {}
    void run() {
      auto rate = std::chrono::microseconds((int) (1e6 / iter_per_sec));
      bool cont = true;
      auto t1 = std::chrono::system_clock::now();
      while (cont) {
        cont = func(this->iter);
        auto t2 = std::chrono::system_clock::now();
        auto rest = rate - (t2 - t1);
        if (rest < std::chrono::microseconds(0)) {
          auto behind = -rest;
          auto lost = behind - behind % rate;
          t1 += lost;
          this->iter += int(lost / rate);
        } else {
          std::this_thread::sleep_for(rest);
        }
        t1 += rate;
        this->iter++;
      }
    }
};

#endif
