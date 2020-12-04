#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

std::vector<int> load_data(const std::string& filename) {
  auto fs = std::fstream{filename};
  std::vector<int> output;
  for(std::string line ; std::getline(fs, line) ; ) {
    if (line != "") {
      output.push_back(std::stoi(line));
    }
  }
  return output;
}

bool swipe(int level, int n, int start, const std::vector<int>& data, int target, std::vector<int>& result) {
  int end = data.size() - (n - level);
  for (auto idx = start ; idx < end ; ++idx) {
    // Set the value for the current level idx
    result [level] = data[idx];
    // If this is the last level compute the sum and compare with target value
    if (level == n) {
      int accu = std::accumulate(result.begin(), result.end(), 0);
      if (accu == target) {
        return true;
      } else {
        return false;
      }
    }

    // Otherwise, swipe over the values in the next level, and break
    // the iteration if the next level reports that it found a solution
    if (swipe(level + 1, n, idx + 1, data, target, result)) {
      return true;
    }
  }

  // If we are here, we didn't find a solution
  return false;
}

std::vector<int> findn(const std::vector<int> input, int n, int target) {
  std::vector<int> candidates(n, 0);
  swipe(0, n, 0, input, target, candidates);
  return candidates;
}

int main(int argc, char** argv) {
    std::cout << "Advent of code 2020. Day 1" << std::endl;

    const std::vector<int> data = load_data("./input.txt");
    const int target_value = 2020;

    // Find 2 and 3 elements that sum to target_value
    for (auto n : {2, 3}) {
      const auto values = findn(data, n, target_value);
      auto value = std::accumulate(values.begin(), values.end(), 1, [](int a, int b) { return a * b; });
      std::cout << "The product of " << n << " values that add to " << target_value
                << " is " << value << std::endl;
    }
}
