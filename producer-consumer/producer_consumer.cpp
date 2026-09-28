#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

std::atomic<int> produced{};
int it{};

constexpr int to_produce{1000};
constexpr std::size_t producer_num{2};
constexpr std::size_t consumer_num{3};

std::mutex cout_mtx;

template <typename T> class threadsafe_queue {
public:
  bool push(T v) {
    std::unique_lock<std::mutex> lk(mtx_);
    limit_cond_.wait(lk,
                     [this] { return q_.size() < buffer_limit_ || closed_; });

    if (closed_)
      return false;

    q_.push(v);
    data_cond_.notify_one();

    return true;
  }

  bool wait_and_pop(T &v) {
    std::unique_lock<std::mutex> lk(mtx_);
    data_cond_.wait(lk, [this] { return !q_.empty() || closed_; });

    if (q_.empty())
      return false;

    v = q_.front();
    q_.pop();
    limit_cond_.notify_one();

    return true;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lk(mtx_);
    return q_.empty();
  }

  std::size_t size() const {
    std::lock_guard<std::mutex> lk(mtx_);
    return q_.size();
  }

  void close() {
    {
      std::lock_guard<std::mutex> lk(mtx_);
      closed_ = true;
    }
    data_cond_.notify_all();
    limit_cond_.notify_all();
  }

private:
  mutable std::mutex mtx_;
  std::queue<T> q_;
  std::condition_variable data_cond_, limit_cond_;
  static constexpr std::size_t buffer_limit_{200};
  bool closed_{};
};

void produce(threadsafe_queue<int> &q) {
  thread_local std::mt19937 rng{std::random_device{}()};
  while (produced.fetch_add(1) < to_produce) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    q.push(static_cast<int>(rng() % 100));
  }
}

void consume(threadsafe_queue<int> &q, int id) {
  int element;
  while (q.wait_and_pop(element)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::lock_guard<std::mutex> lk(cout_mtx);
    std::cout << "Iteration: " << ++it << " Element: " << element
              << " Thread id: " << id << "\n";
  }
}

int main(int argc, char *argv[]) {
  threadsafe_queue<int> q;

  std::vector<std::thread> producers;
  std::vector<std::thread> consumers;

  for (std::size_t i{}; i < producer_num; i++) {
    producers.emplace_back(produce, std::ref(q));
  }

  for (std::size_t i{}; i < consumer_num; i++) {
    consumers.emplace_back(consume, std::ref(q), i);
  }

  for (auto &p : producers)
    p.join();
  q.close();

  for (auto &c : consumers)
    c.join();

  std::cout << "| Consumed: " << it << " |\n";

  return 0;
}
