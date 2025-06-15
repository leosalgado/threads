#include <chrono>
#include <iostream>
#include <string>

#include <shaper.hpp>

int main() {
  const std::string INPUT_FILE = "../data/input/dataset.csv";
  const std::string OUTPUT_PATH = "../data/output/";

  auto start = std::chrono::high_resolution_clock::now();
  auto data = csv::read_csv(INPUT_FILE);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  std::cout << "Reading time: " << duration.count() << "s" << std::endl;

  return 0;
}
