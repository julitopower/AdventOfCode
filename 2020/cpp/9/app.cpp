#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input9.txt"};
  // We use a buffer of 25 entries that we use as a sort of circular
  // buffer. After each iteration we substitue the oldest element in
  // the buffer with the one we just read
  std::vector<int> buffer(25, 0);

  // Part-1 solution
  std::string line;
  std::size_t nline = 0;
  // Fill the buffer
  for (auto i = 0U; i < buffer.size(); ++i) {
    std::getline(fs, line);
    const auto value = std::stoi(line);
    buffer.at(i) = value;
    ++nline;
  }

  // Process one by one the rest of the entries
  int value;
  bool adds_up;
  std::size_t buffer_oldest_idx = 0;
  for (; std::getline(fs, line);) {
    ++nline;
    adds_up = false;
    value = std::stoi(line);
    for (auto i = 0U; i < buffer.size() - 1; ++i) {
      for (auto j = i + 1; j < buffer.size(); ++j) {
        adds_up = (value == buffer.at(i) + buffer.at(j));
        if (adds_up) {
          goto successful_check;
        }
      }
    }

    // Number did not pass the check
    break;

    // After successfully checking the current target number,
    // we update the buffer by overwritting the olders element.
    // This is the same as sliding a window over the input
  successful_check:
    buffer.at(buffer_oldest_idx) = value;
    buffer_oldest_idx = (++buffer_oldest_idx) % buffer.size();
  }

  if (!adds_up) {
    std::cout << "Offending value is: " << value << ", at line " << nline
              << std::endl;
  }

  // Part-2 solution: We use partial sums to find the range of consecutive
  // values that adss up to the target value.
  fs.clear();
  fs.seekg(0);
  std::vector<std::uint64_t> all_numbers;
  std::vector<std::uint64_t> partial_sums;
  int partial_sum = 0;
  // Read all values and calculate partial sums
  for (; std::getline(fs, line);) {
    const auto value = std::stoull(line);
    all_numbers.push_back(value);
    partial_sum += value;
    partial_sums.push_back(partial_sum);
  }

  // Scan through the partial sums taking care of comparing the correct values
  // When a range starts at the position P, the rigth comparison with the
  // partial sums vector requires that partial_sums[P-1] be substracted from the
  // partial sums elements, or added to the target
  std::uint64_t last_value = 0;
  std::size_t start_idx;
  std::size_t end_idx;
  for (auto i = 0U; i < partial_sums.size() - 1; ++i) {
    start_idx = i;
    for (auto it = partial_sums.begin() + i + 1; it != partial_sums.end();
         ++it) {
      if ((*it - last_value) == value) {
        std::cout << "Target found " << value << " " << (*it - last_value)
                  << std::endl;
        // register the end of the range
        end_idx = it - partial_sums.begin() + 1;
        goto found_range;
      }
    }
    last_value = partial_sums[i];
  }

  // Based on the problem input given, we should never find ourselves here
  std::cout << "Not found" << std::endl;
  return 1;

found_range:
  std::cout << "Range [" << start_idx << ", " << end_idx << ")" << std::endl;
  std::sort(all_numbers.begin() + start_idx, all_numbers.begin() + end_idx);
  std::cout << "Part-2 solution: "
            << (all_numbers[start_idx] + all_numbers[end_idx - 1]) << std::endl;
}
