#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <shaper.hpp>

namespace csv {

CsvData read_csv(const std::string &filepath) {
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

void write_state(const CsvData &input_file, const std::string &filepath) {
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

void write_city(const CsvData &input_file, const std::string &filepath) {
  int i = 1;
  std::ofstream new_file(filepath + "cod_cidade.csv");
  std::pair<std::string, std::string> previous;

  new_file << "cod,cidade" << std::endl;
  for (auto &row : input_file.rows) {
    if (row.second != previous.second) {
      new_file << i << "," << row.second << std::endl;
      previous.second = row.second;
      i++;
    }
  }
}

std::unordered_map<std::string, std::string> to_map(const csv::CsvData &csv) {
  std::unordered_map<std::string, std::string> map;
  for (const auto &row : csv.rows) {
    map[row.second] = row.first;
  }
  return map;
}

void normalize_csv(const CsvData &data, const CsvData &state_csv,
                   const CsvData &city_csv, const std::string &filepath) {
  std::ofstream new_file(filepath + "estado_cidade.csv");

  auto state_map = to_map(state_csv);
  auto city_map = to_map(city_csv);

  new_file << "cod_estado,cod_cidade" << std::endl;
  for (const auto &row : data.rows) {
    std::string state_name = row.first;
    std::string city_name = row.second;

    std::string state_code = state_map[state_name];
    std::string city_code = city_map[city_name];

    new_file << state_code << "," << city_code << std::endl;
  }
}

} // namespace csv
