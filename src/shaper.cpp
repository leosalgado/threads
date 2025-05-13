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

  int inc = 1;
  // while (std::getline(file, line)) {
  for (int i = 0; i < 10; i++) {
    std::getline(file, line);
    std::cerr << "Linha lida: " << inc << " " << line << std::endl;
    std::stringstream ss(line);
    std::string cell;
    std::vector<std::string> row;

    while (std::getline(ss, cell, ',')) {
      row.push_back(cell);
    }
    inc++;

    data.rows.push_back(row);
  }
  return data;
}

} // namespace csv
