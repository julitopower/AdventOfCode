#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    std::cout << "Advent of code 2020. Day 4" << std::endl;

    std::fstream fs{"input4.txt"};
    std::set<std::string> required_keys{
      "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
    };
    std::set<std::string> optional_keys{"cid"};

    bool new_record = true;
    std::set<std::string> found_keys{};
    std::size_t valid_entries = 0;
    std::size_t records = 0;
    for(std::string line ; std::getline(fs, line) ; ) {
      if (new_record) {
        ++records;
        found_keys.clear();
      }
      if(line.size() == 0) {
        new_record = true;
        if (found_keys == required_keys) {
          ++valid_entries;
        }
        continue;
      } 

      new_record = false;
      std::stringstream ss {line};
      for (std::string pair ; std::getline(ss, pair, ' ') ; ) {
        auto it = pair.find(":");
        std::string key{pair.begin(), pair.begin() + it};
        if (required_keys.find(key) != required_keys.end()) {
          found_keys.insert(key);
        }
      }
    }

    if (found_keys == required_keys) {
      ++valid_entries;
    }    
    
    std::cout << "Valid entries found: " << valid_entries << "\n";
    std::cout << "Total entries: " << records << "\n";
}
