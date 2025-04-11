#include <iostream>
#include <string>

#include <shaper.hpp>

#define INPUT_FILE "../data/input/dataset.csv"

int main() {
  csv::Shaper shaper;

  auto dados = shaper.read_csv(INPUT_FILE);

  for (const auto &[state, city] : dados) {
    std::cout << state << ", " << city << std::endl;
  }

  return 0;
}
