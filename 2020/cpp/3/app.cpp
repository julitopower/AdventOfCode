#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Coord {
  std::size_t x, y;
};

std::size_t num_trees(const std::vector<std::string>& map, std::size_t dx, std::size_t dy) {
    Coord pos{0, 0};
    std::size_t tree_count = 0;
    while (pos.y < map.size()) {
      tree_count += ((map[pos.y][pos.x] == '#') ? 1 : 0);
      pos.x = (pos.x + dx) % map[0].size();
      pos.y += dy;
    }
    return tree_count;
}

int main(int argc, char** argv) {
    std::cout << "Advent of code 2020. Day 3" << std::endl;
    auto fs = std::fstream{"input3.txt"};
    std::vector<std::string> map;

    for(std::string line ; std::getline(fs, line) ; ) {
      map.push_back(line);
    }

    std::vector<std::pair<std::size_t, std::size_t>> strides {
      {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}
    };
    
    std::size_t tree_count_product = 1;
    for(auto& stride : strides) {
      auto tree_count = num_trees(map, stride.first, stride.second);
      std::cout << "Tree count for stride (" << stride.first << ", "
                << stride.second << "): " << tree_count << "\n";
      tree_count_product *= tree_count;
    }

    std::cout << "Trees count product is: " << tree_count_product << "\n";
}
