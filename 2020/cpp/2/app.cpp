#include <bits/c++config.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <tuple>
#include <sstream>

// Prediate for day one. Character letter must appear a number of times [min, max]
bool predicate_1(const std::string& str, char letter, std::size_t min, std::size_t max) {
  std::size_t times = 0;
  std::for_each(std::begin(str), std::end(str),
                [&times, letter](char l){
                  if (l == letter) {
                    ++times;
                  }
                });
  return ((times >= min) && (times <= max));
}

bool predicate_2(const std::string& str, char letter, std::size_t min, std::size_t max) {
  return (str[min] == letter) ^ (str[max] == letter);
}

std::tuple<int, int, char, std::string> process_line(const std::string& line) {
  // min-max letter: word
  // Split on colon first [rule, word]
  // Split rule on space [min-max, letter]
  // Split min-max on - [min, max]
  std::stringstream ss{line};
  std::string rule, word;
  std::getline(ss, rule, ':');
  std::getline(ss, word, ':');

  ss.clear();
  ss.str(rule);

  std::string minmax, letter;
  std::getline(ss, minmax, ' ');
  std::getline(ss, letter, ' ');

  ss.clear();
  ss.str(rule);

  std::string min, max;
  std::getline(ss, min, '-');
  std::getline(ss, max, '-');

  return std::make_tuple(std::stoi(min), std::stoi(max), letter[0], word);
}

int main(int argc, char** argv) {
  std::cout << "Advent of code 2020. Day 2\n";
  auto fs = std::fstream{"input2.txt"};

  std::size_t count1 = 0;
  std::size_t count2 = 0;
  for(std::string line ; std::getline(fs, line) ; ) {
    int min, max;
    char letter;
    std::string word;
    std::tie(min, max, letter, word) = process_line(line);
    
    if (predicate_1(word, letter, min, max)) { ++count1; }
    if (predicate_2(word, letter, min, max)) { ++count2; }
  }

  std::cout << "Valid passwords for rule 1 found: " << count1 << "\n";
  std::cout << "Valid passwords for rule 2 found: " << count2 << "\n";  
}
