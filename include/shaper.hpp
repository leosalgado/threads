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
  void write_csv(const CsvData &input_file, const std::string &filepath,
                 const std::string &header_name);
};

} // namespace csv
