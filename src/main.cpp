#include <iostream>
#include <omp.h>
#include <string>

#include <shaper.hpp>

int main() {
  const std::string INPUT_FILE = "../data/input/dataset.csv";
  const std::string OUTPUT_PATH = "../data/output/";

  double start = omp_get_wtime();
  auto data = csv::read_csv(INPUT_FILE);

  double end = omp_get_wtime();
  std::cout << "Reading time: " << (end - start) << "s" << std::endl;

  start = omp_get_wtime();
  save_unique_values_per_column(data, OUTPUT_PATH);
  end = omp_get_wtime();
  std::cout << "Saving unique columns time: " << (end - start) << "s"
            << std::endl;

  return 0;
}
