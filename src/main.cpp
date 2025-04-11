#include <iostream>
#include <string>

#include <shaper.hpp>

int main() {
  const std::string INPUT_FILE = "../data/input/dataset.csv";
  const std::string OUTPUT_PATH = "../data/output/";

  csv::Shaper shaper;

  auto data = shaper.read_csv(INPUT_FILE);

  std::cout << data.header.first << ", " << data.header.second << std::endl;

  for (const auto &[state, city] : data.rows) {
    std::cout << state << ", " << city << std::endl;
  }

  return 0;
}
