#include <algorithm>
#include <bits/c++config.h>
#include <cmath>
#include <cstdint>
#include <fenv.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input10.txt"};
  std::vector<std::size_t> adaptors{};
  std::map<std::size_t, std::size_t> diff_count{};
  for (std::string line; std::getline(fs, line);) {
    adaptors.push_back(std::stoul(line));
  }
  std::sort(adaptors.begin(), adaptors.end());

  // Validate the input
  std::size_t prev = 0;
  // See below comment for part 2
  std::map<std::size_t, std::size_t> blocks;
  std::size_t block_size = 0;
  for (auto it = adaptors.begin() ; it != adaptors.end(); ++it) {
    auto value = *it;
    const auto diff = value - prev;
    if (diff == 1) {
      ++block_size;
    } else if (block_size != 0) {
      ++blocks[block_size];
      block_size = 0;
    }
    ++diff_count[diff];
    prev = value;
  }
  
  if (block_size > 1) {
    ++blocks[block_size];
  }

  // Add one extra 3 difference because of the adaptor en the device, which
  // outputs always 3 more than its input;
  ++diff_count[3];

  std::cout << "1-jolt differences: " << diff_count[1]
            << ", 3-jolt differences: " << diff_count[3] << std::endl;
  std::cout << "Product is " << diff_count[1] * diff_count[3] << std::endl;

  // Part-2 requires a math tric:
  // https://schnouki.net/post/2020/advent-of-code-2020-day-10/ Our input only
  // has differences of 3 or 1. We need to count the number of "blocks" of 1s
  // and then apply a multiplicative formula to them

  // factor to apply to each block size: mults = {2: 2, 3: 4, 4: 7, 5: 13}
  std::map<std::size_t, std::size_t> factors{{2, 2}, {3, 4}, {4, 7}, {5, 13}};
  std::uint64_t counter = 1;
  for (auto &p : factors) {
    if (blocks[p.first] == 0) {
      continue;
    }

    auto f = pow(p.second, blocks[p.first]);
    counter *= f;
  }

  std::cout << "Combinations: " << counter << std::endl;

  return 0;
}
