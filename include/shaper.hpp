#pragma once

#include <string>
#include <utility>
#include <vector>
namespace csv {

struct CsvData {
  std::vector<std::pair<std::string, std::string>> rows;
  std::pair<std::string, std::string> header;
};

class Shaper {

public:
  CsvData read_csv(const std::string &filepath);
};

} // namespace csv
