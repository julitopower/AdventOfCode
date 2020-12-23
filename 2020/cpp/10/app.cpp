#include <algorithm>
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
  for (std::size_t value : adaptors) {
    const auto diff = value - prev;
    ++diff_count[diff];
    if (diff < 1 || diff > 3) {
      std::cerr << "Difference is invalid: " << value << " - " << prev
                << std::endl;
    }
    prev = value;
  }

  // Add one extra 3 difference because of the adaptor en the device, which
  // outputs always 3 more than its input;
  ++diff_count[3];

  std::cout << "1-jolt differences: " << diff_count[1]
            << ", 3-jolt differences: " << diff_count[3] << std::endl;
  std::cout << "Product is " << diff_count[1] * diff_count[3] << std::endl;

  return 0;
}
