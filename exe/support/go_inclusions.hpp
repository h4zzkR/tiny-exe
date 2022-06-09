#pragma once
#include <atomic>

namespace twist::stdlike::detail {

class WaitGroupPrimitive {
 public:
  WaitGroupPrimitive() = default;
  void Add() {
    routines_.fetch_add(1);
  }
  void Done() {
    routines_.fetch_sub(1);
    routines_.notify_one();
  }
  void Wait() {
    uint32_t current_routines;
    while ((current_routines = routines_.load()) != 0) {
      routines_.wait(current_routines);
    }
  }

 private:
  std::atomic<uint32_t> routines_{0};
};

}  // namespace twist::stdlike::detail
