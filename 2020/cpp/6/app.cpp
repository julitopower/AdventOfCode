#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input6.txt"};

  // Part-1 solution
  // For each group register the set of positive answers, since we want to
  // count unique answers, we use a set
  std::set<char> answers{};
  // Initialize the positive answers accumulator
  std::size_t sum = 0;

  // Iterate over the group
  for (std::string line; std::getline(fs, line);) {
    // When a new group is been found, summarize its results, reset the set
    // and continue to the next line
    if (line == "") {
      sum += answers.size();
      answers.clear();
      continue;
    }

    std::for_each(line.begin(), line.end(),
                  [&answers](char c) { answers.insert(c); });
  }
  sum += answers.size();
  std::cout << "Sum of different positive answers per group is: " << sum
            << std::endl;

  // Part-2 solution
  fs.clear();
  fs.seekg(0);
  std::map<char, std::size_t> group_answers{};
  std::size_t group_members_count = 0;
  sum = 0;

  // Finds the number of answerw ALL members responded with yes, and adds
  // that number to sum
  auto summarize_group = [&sum, &group_answers, &group_members_count]() {
    std::for_each(group_answers.begin(), group_answers.end(),
                  [&sum, group_members_count](auto p) {
                    if (p.second == group_members_count) {
                      ++sum;
                    }
                  });
    group_answers.clear();
    group_members_count = 0;
  };

  for (std::string line; std::getline(fs, line);) {
    // When a new group is been found, summarize its results, reset the set
    // and continue to the next line
    if (line == "") {
      summarize_group();
      continue;
    }

    std::for_each(line.begin(), line.end(),
                  [&group_answers](char c) { ++group_answers[c]; });
    ++group_members_count;
  }
  // Process the last group, which may have extra information, depending on how
  // the file ends
  summarize_group();

  std::cout << "Per group answer all members said yes, sum: " << sum
            << std::endl;
  return 0;
}
