#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <omp.h>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <shaper.hpp>

namespace csv {
class ThreadedCsvReader {
private:
  // Raw lines
  std::queue<std::string> line_queue;
  // Processed data
  std::queue<std::vector<std::vector<std::string>>> result_queue;

  std::mutex queue_mutex;
  std::mutex result_mutex;
  std::condition_variable cv;
  bool done_reading = false;

  void worker_thread(int thread_id) {
    while (true) {
      std::vector<std::string> chunk;

      {
        std::unique_lock<std::mutex> lock(queue_mutex);
        cv.wait(lock, [this] { return !line_queue.empty() || done_reading; });

        if (line_queue.empty() && done_reading) {
          break;
        }

        for (int i = 0; i < 100 && !line_queue.empty(); ++i) {
          chunk.push_back(line_queue.front());
          line_queue.pop();
        }
      }

      // Processing chunk
      std::vector<std::vector<std::string>> processed_chunk;
      for (const auto &line : chunk) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
          row.push_back(cell);
        }
        processed_chunk.push_back(row);
      }

      {
        std::lock_guard<std::mutex> lock(result_mutex);
        result_queue.push(processed_chunk);
      }
    }
  }

public:
  CsvData
  read_csv_threaded(const std::string &filepath, size_t buffer_size = 8192,
                    int num_threads = std::thread::hardware_concurrency()) {
    std::ifstream file(filepath);
    CsvData data;

    if (!file.is_open()) {
      std::cerr << "Couldn't open file: " << filepath << std::endl;
      return data;
    }

    std::vector<char> buffer(buffer_size);
    file.rdbuf()->pubsetbuf(buffer.data(), buffer_size);

    std::vector<std::thread> workers;
    for (int i = 0; i < num_threads; ++i) {
      workers.emplace_back(&ThreadedCsvReader::worker_thread, this, i);
    }

    std::thread reader_thread([this, &file]() {
      std::string line;
      while (std::getline(file, line)) {
        {
          std::lock_guard<std::mutex> lock(queue_mutex);
          line_queue.push(line);
        }
        cv.notify_one();
      }

      {
        std::lock_guard<std::mutex> lock(queue_mutex);
        done_reading = true;
      }
      cv.notify_all();
    });

    reader_thread.join();

    for (auto &worker : workers) {
      worker.join();
    }

    while (!result_queue.empty()) {
      auto chunk = result_queue.front();
      result_queue.pop();

      for (auto &row : chunk) {
        data.rows.push_back(row);
      }
    }

    return data;
  }
};

CsvData read_csv(const std::string &filepath) {
  ThreadedCsvReader reader;
  return reader.read_csv_threaded(filepath);
}

} // namespace csv
