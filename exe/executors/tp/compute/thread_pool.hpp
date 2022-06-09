#pragma once

#include <exe/executors/executor.hpp>
#include <exe/executors/execute.hpp>

#include <thread>
#include <atomic>
#include <condition_variable>

#include <exe/support/go_inclusions.hpp>
#include <exe/support/blocking_queue.hpp>

#include <vector>

namespace exe::executors::tp::compute {

using exe::executors::Task;
using exe::support::UnboundedBlockingQueue;

// Thread pool for independent CPU-bound tasks
// Fixed pool of worker threads + shared unbounded blocking queue

class ThreadPool : public IExecutor {
 public:
  explicit ThreadPool(size_t workers);
  ~ThreadPool();

  // Non-copyable
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  // IExecutor aka Submit
  // Schedules task for execution in one of the worker threads
  void Execute(TaskBase* task) override;

  // Waits until outstanding work count has reached zero
  void WaitIdle();

  // Stops the worker threads as soon as possible
  // Pending tasks will be discarded
  void Stop();

  // Locates current thread pool from worker thread
  static ThreadPool* Current();

 private:
  void StartWorkerThreads(size_t count);
  void WorkerRoutine();

  // Worker threads, task queue, etc
  UnboundedBlockingQueue tasks_;
  std::vector<std::thread> workers_;
  twist::stdlike::detail::WaitGroupPrimitive wg_;

  std::atomic<bool> stopped_{false};
};

inline ThreadPool* Current() {
  return ThreadPool::Current();
}

}  // namespace exe::executors::tp::compute
