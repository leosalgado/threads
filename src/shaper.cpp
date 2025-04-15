#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <shaper.hpp>

namespace csv {

CsvData Shaper::read_csv(const std::string &filepath) {
  std::ifstream file(filepath);
  CsvData data;
  std::string line;

  if (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string first, second;

    if (std::getline(ss, first, ',') && std::getline(ss, second)) {
      data.header = {first, second};
    }
  }

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string first, second;

    if (std::getline(ss, first, ',') && std::getline(ss, second)) {
      data.rows.emplace_back(first, second);
    }
  }
  return data;
}

void Shaper::write_state(const CsvData &input_file,
                         const std::string &filepath) {
  std::string line;

  int i = 1;
  std::ofstream new_file(filepath + "cod_estado.csv");
  std::pair<std::string, std::string> previous;

  new_file << "cod,estado" << std::endl;
  for (auto &row : input_file.rows) {
    if (row.first != previous.first) {
      new_file << i << "," << row.first << std::endl;
      previous.first = row.first;
      i++;
    }
  }
}

void Shaper::write_city(const CsvData &input_file,
                        const std::string &filepath) {
  int i = 1;
  std::ofstream test_file(filepath + "cod_cidade.csv");
  std::pair<std::string, std::string> previous;

  test_file << "cod,cidade" << std::endl;
  for (auto &row : input_file.rows) {
    if (row.second != previous.second) {
      test_file << i << "," << row.second << std::endl;
      previous.second = row.second;
      i++;
    }
  }
}

} // namespace csv
