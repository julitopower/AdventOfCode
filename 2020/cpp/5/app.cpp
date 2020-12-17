#include <bits/c++config.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <numeric>
#include <string>
#include <bitset>

std::size_t to_bin(const char &c, char zero = 'F', char one = 'B') {
  return (c == one) ? 1 : 0;
}

std::size_t row_nb(const std::string &str) {
  return std::accumulate(
      str.begin(), str.end() - 3, 0U,
      [](std::size_t acc, char c) { return (acc << 1) + to_bin(c); });
}

std::size_t col_nb(const std::string &str) {
  return std::accumulate(
      str.begin() + 7, str.end(), 0U,
      [](std::size_t acc, char c) { return (acc << 1) + to_bin(c, 'L', 'R'); });
}

std::size_t get_seat(const std::string& str) {
  return row_nb(str) * 8 + col_nb(str);  
}

int main(int argc, char *argv[]) {
  std::ifstream fs{"input5.txt"};
  std::size_t max = 0;

  // Solution to part 1
  for (std::string line; std::getline(fs, line);) {
    std::size_t val = get_seat(line);
    if (val > max) {
      max = val;
    }
  }

  constexpr auto max_seat = 128 * 8 - 1;
  fs.clear();
  fs.seekg(0);
  std::bitset<max_seat> positions{};
  for (std::string line; std::getline(fs, line);) {
    std::size_t val = get_seat(line);
    positions.set(val);
  }

  for (auto i = 1U ; i < max_seat ; ++i){
    if (!positions.test(i) && positions.test(i - 1) && positions.test(i + 1)) {
      std::cout << "Your seat is: " << i << "\n";
      break;
    }
  }

  std::cout << "Max seat is: " << max << std::endl;
  return 0;
}
