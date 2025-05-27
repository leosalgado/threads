#pragma once

#include <string>
#include <vector>
namespace csv {

struct CsvData {
  std::vector<std::vector<std::string>> rows;
};

CsvData read_csv(const std::string &filepath);

void save_unique_values_per_column(const CsvData &data,
                                   const std::string &base_filename);

} // namespace csv
