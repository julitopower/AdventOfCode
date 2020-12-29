#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input13.txt"};
  std::vector<std::pair<int, int>> buses;
  std::string line;
  std::getline(fs, line);
  const std::size_t earliest = std::stoull(line);
  for (std::string line; std::getline(fs, line, ',');) {
    if (line[0] == 'x') {
      continue;
    }
    const auto busid = std::stoull(line);
    buses.push_back({earliest % busid, busid});
  }
  std::sort(buses.begin(), buses.end());
  auto sol_1 = (buses.back().second - buses.back().first) * buses.back().second;
  std::cout << "Solution 1: " << sol_1 << std::endl;

  return 0;
}
