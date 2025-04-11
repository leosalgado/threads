#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <shaper.hpp>

namespace csv {

std::vector<std::pair<std::string, std::string>>
Shaper::read_csv(const std::string &filepath) {
  std::ifstream file(filepath);
  std::vector<std::pair<std::string, std::string>> data;
  std::string line;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string first, second;

    if (std::getline(ss, first, ',') && std::getline(ss, second)) {
      data.emplace_back(first, second);
    }
  }
  return data;
}

} // namespace csv
