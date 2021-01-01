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
#include <bits/c++config.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

// This class can be used to solve part-2. As we read the mask
// We can represent the memory addresses and the value of the
// memory address read from the file as a Binary, and bit by bit
// fill its contents
class Binary {
public:
  Binary(std::uint64_t value) : value_{value} {}
  bool operator[](std::size_t idx) const { return value_ & (0x1ULL << idx); }
  void set(std::size_t idx) { value_ = (value_ | (0x1ULL << idx)); }
  void unset(std::size_t idx) { value_ = (value_ ^ (0x1ULL << idx)); }
  void reset(std::uint64_t value) { value_ = value; }
  std::uint64_t get() const { return value_; }

private:
  std::uint64_t value_;
};

int main(int argc, char *argv[]) {
  // Part-1
  {
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
        const std::uint64_t value =
            std::stoull(line.substr(line.find("=") + 1));
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
  }

  // Part-2: Out of the mask we build 3 elemets. One mask to force bits to 1,
  // one mask to force bits to zero, and a set of values corresponding to all
  // the permutations of the bits marked with X. To calcualte the memory
  // addresses we set the required bits to one, and then set to zero the bits of
  // the floating values. Then we add to the resulting base memory address, one
  // by one, the values corresponding to the permutations of the bits marked
  // with X.
  {
    std::ifstream fs{"input14.txt"};
    std::map<std::uint64_t, std::uint64_t> mem;
    // The mask used to set certain bits to one
    Binary one_mask{0ULL};
    // The mask used to set the 'X' bits to zero
    Binary zero_mask{~0ULL};
    // Values resulting of permuting the 'X' bits
    std::vector<std::uint64_t> values{0};
    std::vector<std::uint64_t> values_aux{};

    // Read line by line
    for (std::string line; std::getline(fs, line);) {
      if (line.find("mask") == 0) {
        // New mask, reset the masks and value vectors
        one_mask.reset(0ULL);
        zero_mask.reset(~0ULL);
        values.clear();
        values.push_back(0);
        values_aux.clear();

        const std::string mask = line.substr(line.rfind(" "));
        // Index i in the string corresponsd to bit (str.size() - i + 1).
        // So we read char i from the string, but write in (str.size() - i + 1)
        // on the masks
        for (auto i = 0U; i < mask.size(); ++i) {
          const auto idx = mask.size() - i - 1;
          const char c = mask[i];

          if (c == '1') {
            one_mask.set(idx);
          } else if (c == 'X') {
            zero_mask.unset(idx);
            // Generate values permuting bit idx
            for (auto val : values) {
              values_aux.push_back(val);
              values_aux.push_back(val + (0x1ULL << idx));
            }
            values = values_aux;
            values_aux.clear();
          }
        }
      } else {
        // Extract teh value
        const std::uint64_t value =
            std::stoull(line.substr(line.find("=") + 1));

        // Extract the memory address
        const auto init = line.find("[") + 1;
        const auto end = line.rfind("]");
        auto mem_addr = std::stoull(line.substr(init, end - init));
        // Get the base memory address
        mem_addr = ((mem_addr | one_mask.get()) & zero_mask.get());
        // Set all memory positions using base_mem_address + value
        for (auto v : values) {
          mem[mem_addr + v] = value;
        }
      }
    }

    // Accumulate the values in the map
    const std::uint64_t acc = std::accumulate(
        mem.begin(), mem.end(), 0ULL,
        [](std::uint64_t acc, const auto &p) { return acc + p.second; });
    std::cout << acc << std::endl;
  }

  return 0;
}
