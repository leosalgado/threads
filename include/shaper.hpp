#pragma once

#include <string>
#include <vector>
namespace csv {

struct CsvData {
  std::vector<std::vector<std::string>> rows;
};

CsvData read_csv(const std::string &filepath);

} // namespace csv
