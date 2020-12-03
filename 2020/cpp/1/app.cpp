#include <iostream>
#include <fstream>
#include <vector>

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

int main(int argc, char** argv) {
    std::cout << "Advent of code 2020. Day 1" << std::endl;

    const std::vector<int> data = load_data("./input.txt");

    const int target_value = 2020;
    // N^2 traversal to find matching pair
    int offset = 0;
    for (int v1 : data) {
      for (auto it = data.begin() + offset ; it != data.end() ; ++it) {
        if ((v1 + *it) == target_value) {
          std::cout << (v1 * (*it)) << std::endl;
        }
      }
      ++offset;
    }
}
