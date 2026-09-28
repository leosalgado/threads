#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;

int main(int argc, char *argv[]) {

  const unsigned int thread_num = [] {
    const auto n = std::thread::hardware_concurrency();
    return n > 0 ? n : 1;
  }();

  int count{};

  std::vector<std::thread> workers;

  for (int i{}; i < thread_num; i++) {
    workers.emplace_back([&count, i] {
      int res{};
      for (int j{}; j < 10000; j++) {
        std::unique_lock<std::mutex> lock(mtx);
        res = ++count;
        lock.unlock();
        std::cout << "thread id:" << i << " " << res << "\n";
      }
    });
  }

  for (auto &w : workers) {
    w.join();
  }

  std::cout << "Final count value: " << count << "\n";

  return 0;
}
