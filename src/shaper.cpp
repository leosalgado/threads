#include <algorithm>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <shaper.hpp>

namespace csv {

CsvData read_csv(const std::string &filepath) {
  std::ifstream file(filepath);
  CsvData data;

  if (!file.is_open()) {
    std::cerr << "Couldn't open file: " << filepath << std::endl;
    return data;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  size_t total_lines = lines.size();
  data.rows.resize(total_lines);

#pragma omp parallel for
  for (size_t i = 0; i < total_lines; ++i) {
    std::stringstream ss(lines[i]);
    std::string cell;
    std::vector<std::string> row;

    while (std::getline(ss, cell, ',')) {
      row.push_back(cell);
    }

    data.rows[i] = row;
  }

  return data;
}

void save_unique_values_per_column(const CsvData &data,
                                   const std::string &base_filename) {
  if (data.rows.empty())
    return;

  size_t num_columns = data.rows[0].size();

  std::set<size_t> drop_columns = {0, 9, 10, 11, 12, 13, 14, 15, 16, 21, 22};

#pragma omp parallel for
  for (size_t col = 0; col < num_columns; ++col) {

    if (drop_columns.find(col) != drop_columns.end()) {
      continue;
    }

    std::set<std::string> unique_values;

    for (size_t row = 1; row < data.rows.size(); ++row) {
      unique_values.insert(data.rows[row][col]);
    }

    std::string col_name = data.rows[0][col];
    col_name.erase(std::remove(col_name.begin(), col_name.end(), '\r'),
                   col_name.end());
    col_name.erase(std::remove(col_name.begin(), col_name.end(), '\n'),
                   col_name.end());

    std::string filename = base_filename + col_name + ".csv";
    std::ofstream file(filename);

    if (!file.is_open()) {
#pragma omp critical
      std::cerr << "Couldn't open file: " << filename << std::endl;
      continue;
    }

    file << "cod" << "," << data.rows[0][col] << std::endl;

    int id = 1;
    for (const auto &val : unique_values) {
      file << id++ << "," << val << std::endl;
    }
  }
}

} // namespace csv
