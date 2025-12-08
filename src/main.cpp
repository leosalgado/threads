#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define DELIMITER ','

struct CsvData {
  std::vector<std::string> headers;
  std::vector<std::vector<std::string>> rows;
};

CsvData parse_csv(std::ifstream &file) {
  CsvData out;
  std::string line;

  std::getline(file, line);
  std::stringstream header_stream(line);
  std::string header;
  while (std::getline(header_stream, header, DELIMITER)) {
    out.headers.push_back(header);
  }

  while (std::getline(file, line)) {
    std::stringstream row_stream(line);
    std::string val;
    std::vector<std::string> row;
    while (std::getline(row_stream, val, DELIMITER)) {
      row.push_back(val);
    }
    out.rows.push_back(std::move(row));
  }
  return out;
}

std::vector<std::unordered_map<std::string, int>>
create_dicts(const CsvData &data) {
  size_t col_cnt = data.headers.size();
  std::vector<std::unordered_map<std::string, int>> dicts(col_cnt);

  for (size_t c{}; c < col_cnt; c++) {
    std::unordered_set<std::string> uniques;
    for (auto &row : data.rows) {
      if (c < row.size()) {
        uniques.insert(row[c]);
      }
    }

    int id = 1;
    for (auto &u : uniques) {
      dicts[c][u] = id++;
    }
  }
  return dicts;
}

int main() {

  std::ifstream file("../data/input/dataset.csv");
  if (!file) {
    std::cerr << "Couldn't open file" << std::endl;
  }

  auto data = parse_csv(file);

  auto dicts = create_dicts(data);

  for (auto &v : dicts) {
    for (auto &m : v) {
      std::cout << m.first << DELIMITER << m.second << std::endl;
    }
  }

  return 0;
}
