#include <iostream>
#include <string>

#include <shaper.hpp>

int main() {
  const std::string INPUT_FILE = "../data/input/dataset.csv";
  const std::string OUTPUT_PATH = "../data/output/";

  auto data = csv::read_csv(INPUT_FILE);

  return 0;
}
