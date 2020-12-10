#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Coord {
  std::size_t x, y;
};

int main(int argc, char** argv) {
    std::cout << "Advent of code 2020. Day 3" << std::endl;
    auto fs = std::fstream{"input3.txt"};
    std::vector<std::string> map;

    for(std::string line ; std::getline(fs, line) ; ) {
      map.push_back(line);
    }

    Coord pos{0, 0};
    std::size_t tree_count = 0;
    while (pos.y < map.size()) {
      tree_count += ((map[pos.y][pos.x] == '#') ? 1 : 0);
      pos.x = (pos.x + 3) % map[0].size();
      pos.y += 1;
    }

    std::cout << "Trees encountered: " << tree_count << "\n";
    
}
