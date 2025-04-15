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

  void write_state(const CsvData &input_file, const std::string &filepath);

  void write_city(const CsvData &input_file, const std::string &filepath);

  void normalize_csv(const CsvData &data, const CsvData &state_csv,
                     const CsvData &city_csv, const std::string &filepath);
};

} // namespace csv
