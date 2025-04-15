#include <iostream>
#include <string>

#include <shaper.hpp>

int main() {
  const std::string INPUT_FILE = "../data/input/dataset.csv";
  const std::string OUTPUT_PATH = "../data/output/";

  csv::Shaper shaper;

  auto data = shaper.read_csv(INPUT_FILE);

  shaper.write_state(data, OUTPUT_PATH);
  shaper.write_city(data, OUTPUT_PATH);

  return 0;
}
