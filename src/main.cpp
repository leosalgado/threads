#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

std::vector<std::unordered_map<std::string, int>>
read_csv(std::ifstream &file) {
  std::string line;

  std::getline(file, line);
  std::stringstream header_stream(line);
  std::string header;
  int col_cnt{};

  while (std::getline(header_stream, header, ',')) {
    col_cnt++;
  }

  std::cout << "COL COUNT: " << col_cnt << "\n=============" << std::endl;

  std::vector<std::unordered_map<std::string, int>> columns_map(col_cnt);

  while (std::getline(file, line)) {
    std::stringstream row(line);
    std::string val;
    int col_idx{};

    while (std::getline(row, val, ',')) {
      if (col_idx < col_cnt) {
        auto &colmap = columns_map[col_idx];

        if (!colmap.contains(val)) {
          colmap[val] = colmap.size() + 1;
        }
      }
      col_idx++;
    }
  }
  return columns_map;
}

int main() {

  std::ifstream file("../data/input/dataset.csv");
  if (!file) {
    std::cerr << "Couldn't open file" << std::endl;
  }

  auto data = read_csv(file);

  for (auto &v : data) {
    for (auto &map : v) {
      std::cout << map.first << "," << map.second << std::endl;
    }
    std::cout << "=============" << std::endl;
  }

  return 0;
}
