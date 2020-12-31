/*
  Divide the mask into and AND and an OR masks. The OR one is responsible for
  turning ON certain bits, marked as 1 in the input. The AND mask is used to
  turn off certain bits marked as 0 in the input. Both masks must leave bits
  marked as 'X' in the input unchanged.

  OR_MASK = Input with 'X' bits set to 0
  AND_MASK = Input with 'X' bits set to 1

  As we read the entries we build the 2 masks, and apply them to the values.
  Finally we just sum all the values. We will use 64 bits unsigned integers to
  represent the memory.

  The memory can be represented as a Map<address, value>. The problem contains
  around 550 values, so this it perfectly acceptable. Another, possibly more
  efficient representation, in terms of memory traversal, would keep the values
  in a vector, and would maintain a Map<address, position_in_vector>. This way
  all values would be in a single memory block.
 */
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream fs{"input14.txt"};
  std::map<std::uint64_t, std::uint64_t> mem;
  std::uint64_t or_mask = 0x0ULL;
  std::uint64_t and_mask = ~or_mask;
  for (std::string line; std::getline(fs, line);) {
    if (line.find("mask") == 0) {
      or_mask = 0x0ULL;
      and_mask = ~or_mask;
      const std::string mask = line.substr(line.rfind(" "));
      for (char c : mask) {
        // Shift left one position, and make sure the or mask has
        // a 0, and the and one has a 1, so that they don't alter
        // this position when applied to a value
        or_mask = or_mask << 1;
        and_mask = (and_mask << 1) | 0x1LL;

        // For 'X' there is nothing to do
        if (c == 'X') {
          continue;
        }

        if (c == '1') { // Write a 1 in LSB
          or_mask |= 0x1ULL;
          and_mask |= 0x1ULL;
        } else { // Write a 0 in LSB
          or_mask &= ~0x1ULL;
          and_mask &= ~0x1ULL;
        }
      }
    } else {
      const std::uint64_t value = std::stoull(line.substr(line.find("=") + 1));
      const auto init = line.find("[") + 1;
      const auto end = line.rfind("]");
      const auto mem_addr = std::stoull(line.substr(init, end - init));
      mem[mem_addr] = ((value | or_mask) & and_mask);
    }
  }

  // Accumulate the values in the map
  const std::uint64_t acc = std::accumulate(
      mem.begin(), mem.end(), 0ULL,
      [](std::uint64_t acc, const auto &p) { return acc + p.second; });
  std::cout << acc << std::endl;
  return 0;
}
