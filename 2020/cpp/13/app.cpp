#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input13.txt"};
  // For part 1, vector of <module, busid>
  std::vector<std::pair<int, int>> bs;
  std::string line;
  std::getline(fs, line);
  const std::size_t earliest = std::stoull(line);

  // For Part-2
  // Step for next candidate to probe
  std::size_t factor = 1;
  // Candidate value
  std::size_t candidate = 0;
  // Offset of the start time of the current bus
  std::size_t offset = 0;
  for (std::string line; std::getline(fs, line, ',');) {
    if (line[0] == 'x') {
      ++offset;
      continue;
    }
    const auto busid = std::stoull(line);
    // For Part-1, fill the <module, busid> vector
    bs.push_back({earliest % busid, busid});

    // For Part-2, find the next candidate that fullfills the
    // requirement for the current bus. Once we find a suitable
    // candiate, the next one will be factor * busid units away.
    // This way, each time we find a new suitable candidate, the
    // next candidate to try is further and further away.
    while (true) {
      candidate += factor;
      if ((candidate + offset) % busid == 0) {
        factor *= busid;
        break;
      }
    }
    ++offset;
  }
  std::sort(bs.begin(), bs.end());
  auto sol_1 = (bs.back().second - bs.back().first) * bs.back().second;
  std::cout << "Solution 1: " << sol_1 << std::endl;
  std::cout << "Solution 2: " << candidate << std::endl;

  return 0;
}
