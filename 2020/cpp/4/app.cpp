#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

namespace {
bool val_r(const std::string &str, std::size_t min, std::size_t max) {
  try {
    auto n_value = std::stoi(str);
    return (n_value >= min && n_value <= max);
  } catch (...) {
  }
  return false;
}

std::pair<std::size_t, std::size_t>
process(const std::string filename, const std::set<std::string> required_keys,
        std::map<std::string, std::function<bool(const std::string &)>>
            validations) {
  std::fstream fs{filename};
  bool new_record = true;
  std::set<std::string> found_keys{};
  std::size_t valid_entries = 0;
  std::size_t records = 0;
  for (std::string line; std::getline(fs, line);) {
    if (new_record) {
      ++records;
      found_keys.clear();
    }
    if (line.size() == 0) {
      new_record = true;
      if (found_keys == required_keys) {
        ++valid_entries;
      }
      continue;
    }

    new_record = false;
    std::stringstream ss{line};
    for (std::string pair; std::getline(ss, pair, ' ');) {
      auto it = pair.find(":");
      std::string key{pair.begin(), pair.begin() + it};
      std::string value{pair.begin() + it + 1, pair.end()};
      if (required_keys.find(key) != required_keys.end()) {
        if ((*validations.find(key)).second(value)) {
          found_keys.insert(key);
        }
      }
    }
  }

  if (found_keys == required_keys) {
    ++valid_entries;
  }

  return {valid_entries, records};
}

std::pair<std::size_t, std::size_t>
process(const std::string filename, const std::set<std::string> required_keys) {
  std::map<std::string, std::function<bool(const std::string &)>> validations;
  std::for_each(required_keys.begin(), required_keys.end(),
                [&validations](const std::string &key) {
                  validations.insert(std::make_pair(
                      key, [](const std::string &) { return true; }));
                });
  return process(filename, required_keys, validations);
}

} // namespace

int main(int argc, char **argv) {
  std::cout << "Advent of code 2020. Day 4" << std::endl;

  // As per the problem definition, these keys must exists in all records
  std::set<std::string> required_keys{"byr", "iyr", "eyr", "hgt",
                                      "hcl", "ecl", "pid"};

  // For part2, values must pass certain validations. We store the validation
  // associated with the value of each key in a map. Validations are simply
  // predicates
  std::map<std::string, std::function<bool(const std::string &)>> validations;
  // byr (Birth Year) - four digits; at least 1920 and at most 2002.
  validations.insert(
      {"byr", [](const std::string &val) { return val_r(val, 1920, 2002); }});
  // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
  validations.insert(
      {"iyr", [](const std::string &val) { return val_r(val, 2010, 2020); }});
  // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
  validations.insert(
      {"eyr", [](const std::string &val) { return val_r(val, 2020, 2030); }});
  /*
    hgt (Height) - a number followed by either cm or in:
        If cm, the number must be at least 150 and at most 193.
        If in, // TODO: he number must be at least 59 and at most 76.
   */  
  validations.insert({"hgt", [](const std::string &val) {
                        try {
                          std::stringstream ss{val};
                          std::size_t n_val;
                          std::string unit;
                          ss >> n_val >> unit;
                          if (unit == "cm") {
                            return (n_val >= 150 && n_val <= 193);
                          } else if (unit == "in") {
                            return (n_val >= 59 && n_val <= 76);
                          }
                        } catch (...) {
                        }
                        return false;
                      }});
  // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
  validations.insert(
      {"hcl", [](const std::string &val) {
         try {
           if (val.size() != 7) {
             return false;
           }
           if (val[0] != '#') {
             return false;
           }
           return std::all_of(val.begin() + 1, val.end(), [](char chr) {
             return (chr >= '0' && chr <= '9') || (chr >= 'a' && chr <= 'f');
           });
         } catch (...) {
         }
         return false;
       }});
  // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
  validations.insert({"ecl", [](const std::string &val) {
                        std::set<std::string> valid{"amb", "blu", "brn", "gry",
                                                    "grn", "hzl", "oth"};
                        return (valid.find(val) != valid.end());
                      }});
  // pid (Passport ID) - a nine-digit number, including leading zeroes.
  validations.insert({"pid", [](const std::string &val) {
                        try {
                          auto v = std::stoi(val);
                          return val.size() == 9;
                        } catch (...) {
                        }
                        return false;
                      }});
  std::set<std::string> optional_keys{"cid"};

  // Solution to part-1
  {
    auto [valid_entries, records] = process("input4.txt", required_keys);
    std::cout << "Valid entries with required keys found: " << valid_entries << "\n";
    std::cout << "Total entries: " << records << "\n";
  }

  // Solution to part-2
    {
    auto [valid_entries, records] =
        process("input4.txt", required_keys, validations);
    std::cout << "Valid entries with full validation found: " << valid_entries << "\n";
    std::cout << "Total entries: " << records << "\n";
  }
}
