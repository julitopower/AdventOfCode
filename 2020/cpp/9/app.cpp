#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input9.txt"};
  std::vector<int> buffer(25, 0);

  std::string line;
  // Fill the buffer
  for (auto i = 0U; i < buffer.size(); ++i) {
    std::getline(fs, line);
    const auto value = std::stoi(line);
    buffer.at(i) = value;
  }

  // Process one by one the rest of the entries
  int value;
  bool adds_up;
  std::size_t buffer_oldest_idx = 0;
  for (; std::getline(fs, line);) {
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

  successful_check:
    buffer.at(buffer_oldest_idx) = value;
    buffer_oldest_idx = (++buffer_oldest_idx) % buffer.size();
  }

  if (!adds_up) {
    std::cout << "Offending value is: " << value << std::endl;
    return 0;
  }

  return 1;
}
