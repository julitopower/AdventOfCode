#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

int main(int argc, char *argv[])
{
  std::ifstream fs{"input6.txt"};

  // For each group register the set of positive answers, since we want to
  // count unique answers, we use a set
  std::set<char> answers{};
  // Initialize the positive answers accumulator
  std::size_t sum = 0;

  // Iterate over the group
  for (std::string line ; std::getline(fs, line) ; ) {
    // When a new group is been found, summarize its results, reset the set
    // and continue to the next line
    if (line == "") {
      sum += answers.size();
      answers.clear();
      continue;
    }

    std::for_each(line.begin(), line.end(),
                  [&answers](char c) {
                    answers.insert(c);
                  });
  }
  sum += answers.size();  
  std::cout << "Sum of different positive answers per group is: " << sum << std::endl;
  return 0;
}
