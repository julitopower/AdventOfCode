#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

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

int main(int argc, char *argv[]) {
  std::fstream fs{"input5.txt"};
  std::size_t max = 0;
  for (std::string line; std::getline(fs, line);) {
    std::size_t val = row_nb(line) * 8 + col_nb(line);
    if (val > max) {
      max = val;
    }
  }

  std::cout << "Max seat is: " << max << std::endl;
  return 0;
}
