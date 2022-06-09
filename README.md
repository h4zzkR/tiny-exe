# TinyExe

Execution components for C++ projects

CMake template: https://gitlab.com/Lipovsky/wheels

# Usage:
```cpp
  ThreadPool pool{3}; // init threadpool with 3 workers
  Execute(pool, [&]() {
      std::cout << "Hello\n";
  }); // submit task to execute
  
  pool.WaitIdle(); // wait untill all tasks done
  pool.Stop(); // stop workers, release threads
```
