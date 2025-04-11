#pragma once

#include <string>
#include <utility>
#include <vector>
namespace csv {

class Shaper {

public:
  std::vector<std::pair<std::string, std::string>>
  read_csv(const std::string &filepath);
};

} // namespace csv
