#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/* Remove 1 space from the left, and 1 '.' or space
   from the right. This is clearly a very constrained trim
*/
std::string trim(const std::string &str) {
  std::string aux = str;
  if (aux[0] == ' ')
    aux = aux.substr(1);
  if (aux.back() == '.' || aux.back() == ' ')
    aux.pop_back();
  return aux;
}

/* In a string containing serveral wrods separated by ' ', remove the
   right-most one.
*/
std::string remove_last_word(const std::string &str) {
  auto pos = str.rfind(" ");
  return str.substr(0, pos);
}

/* In a string containing serveral wrods separated by ' ', remove the
   left-most one.
*/
std::string remove_first_word(const std::string &str) {
  auto pos = str.find(" ");
  return str.substr(pos + 1);
}

std::string get_first_word(const std::string &str) {
  auto pos = str.find(" ");
  return str.substr(0, pos);
}

/* Build the map from bag to the bags it can contain
 */
std::map<std::string, std::vector<std::pair<std::size_t, std::string>>>
build_bag_map(const std::string &filename) {
  // This is the word that separates a bag type from its possible
  // containers.
  const std::string CONTAIN = "contain";

  std::ifstream fs{filename};
  std::map<std::string, std::vector<std::pair<std::size_t, std::string>>> contains;
  for (std::string line; std::getline(fs, line);) {
    // Split the color bag from its list of containers
    auto pos = line.find(CONTAIN);
    auto keystr = remove_last_word(trim(line.substr(0, pos)));
    auto valuesstr = trim(line.substr(pos + CONTAIN.size()));

    // Split the list of containers and populate the map
    std::stringstream ss{valuesstr};
    for (std::string value; std::getline(ss, value, ',');) {
      value = remove_last_word(trim(value));
      if (value == "no other") {
        continue;
      }
      
      const auto quantity = std::stoi(get_first_word(value));
      value = remove_first_word(value);
      contains[keystr].push_back(std::make_pair(quantity, value));
    }
  }

  return contains;
}

/* Builds a map from bag color, to a list of bag colors that
   can contain it. This esentially represents a graph in which
   each node has edges pointing to the bag colors that can
   contain it.
*/
std::map<std::string, std::vector<std::string>>
build_color_map(const std::string &filename) {
  const auto contains = build_bag_map(filename);
  std::map<std::string, std::vector<std::string>> containers_of;
  for (auto pair : contains) {
    const auto key = pair.first;
    const auto values = pair.second;
    for (auto p : values) {
      containers_of[p.second].push_back(key);
    }
  }
  return containers_of;
}

int main(int argc, char *argv[]) {
  const auto target = "shiny gold";
  auto containers_of = build_color_map("input7.txt");

  // Traversal to solve Day7-1
  std::set<std::string> visited{};
  std::vector<std::string> pending{target};
  while (!pending.empty()) {
    auto val = pending.back();
    pending.pop_back();

    // This container has already been expanded, move on
    if (visited.count(val) == 1) {
      continue;
    }

    // Add the color bags that can contain the current container
    // to the pending list
    for (auto container : containers_of[val]) {
      pending.push_back(container);
    }
    visited.insert(val);
  }

  // A bag cannot contain itself, so the right values is visited - 1
  std::cout << "Colors that can contain shinny gold " << (visited.size() - 1)
            << std::endl;

  // Day7-2
  auto contains = build_bag_map("input7.txt");
  
  return 0;
}
