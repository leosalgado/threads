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

} // namespace csv
