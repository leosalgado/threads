#include <string>

#include <shaper.hpp>

int main() {
  const std::string INPUT_FILE = "../data/input/dataset.csv";
  const std::string OUTPUT_PATH = "../data/output/";

  auto data = csv::read_csv(INPUT_FILE);

  csv::write_state(data, OUTPUT_PATH);
  csv::write_city(data, OUTPUT_PATH);

  auto state_csv = csv::read_csv(OUTPUT_PATH + "cod_estado.csv");
  auto city_csv = csv::read_csv(OUTPUT_PATH + "cod_cidade.csv");

  csv::normalize_csv(data, state_csv, city_csv, OUTPUT_PATH);

  return 0;
}
