#include <cstdio>
#include <fstream>
#include <iostream>
#include <mutex>
#include <omp.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <shaper.hpp>

std::mutex file_mutex;

namespace csv {

CsvData read_csv(const std::string &filepath) {
  std::ifstream file(filepath);
  CsvData data;
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Couldn't open file: " << filepath << std::endl;
    return data;
  }

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string cell;
    std::vector<std::string> row;

    while (std::getline(ss, cell, ',')) {
      row.push_back(cell);
      std::cout << cell << std::endl;
    }

    data.rows.push_back(row);
  }
  return data;
}

} // namespace csv
