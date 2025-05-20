#include <fstream>
#include <iostream>
#include <omp.h>
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

} // namespace csv
