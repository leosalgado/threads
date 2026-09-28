#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;

int main(int argc, char *argv[]) {

  constexpr std::size_t total_work = 10003;

  const unsigned int thread_num = [] {
    const auto n = std::thread::hardware_concurrency();
    return n > 0 ? n : 1;
  }();

  const std::size_t base_work = total_work / thread_num;
  const std::size_t rest = total_work % thread_num;

  std::vector<std::thread> workers;

  int glob_count{};

  for (std::size_t i{}; i < thread_num; i++) {
    std::size_t work{};
    if (i < rest)
      work = base_work + 1;
    else
      work = base_work;

    workers.emplace_back([&glob_count, work, i] {
      int count{};
      for (std::size_t j{}; j < work; j++) {
        count++;
        std::cout << "Thread id:" << i << " " << count << "\n";
      }
      std::lock_guard<std::mutex> lock(mtx);
      glob_count += count;
    });
  }

  for (auto &w : workers) {
    w.join();
  }

  std::cout << "Final count value: " << glob_count << "\n";

  return 0;
}
