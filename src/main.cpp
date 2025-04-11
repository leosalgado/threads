#include <iostream>
#include <string>

#include <shaper.hpp>

#define INPUT_FILE "../data/input/dataset.csv"
#define OUTPUT_PATH "../data/output/"

int main() {
  csv::Shaper shaper;

  auto data = shaper.read_csv(INPUT_FILE);

  std::cout << data.header.first << ", " << data.header.second << std::endl;

  for (const auto &[state, city] : data.rows) {
    std::cout << state << ", " << city << std::endl;
  }

  return 0;
}
