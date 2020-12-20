#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

enum class Ops { ACC, JMP, NOOP };

class Memory {
public:
  void add_instruction(Ops op_code, int value = 0) {
    mem_.push_back({op_code, value});
  }

  void set(std::size_t idx, Ops op_code, int value) {
    mem_.at(idx) = std::make_pair(op_code, value);
  }

  const std::pair<Ops, int> &read(std::size_t idx) const {
    return mem_.at(idx);
  }

  std::size_t size() const { return mem_.size(); }

private:
  std::vector<std::pair<Ops, int>> mem_;
};

class CPU {
public:
  void reset() {
    pc_ = 0;
    acc_ = 0;
  }

  int accumulator() { return acc_; }

  void run_next(const Memory &mem) {
    auto inst = mem.read(pc_);
    switch (inst.first) {
    case Ops::ACC:
      acc_ += inst.second;
      ++pc_;
      break;
    case Ops::JMP:
      pc_ += inst.second;
      break;
    case Ops::NOOP:
      ++pc_;
      break;
    }
  }

  std::size_t pc() const { return pc_; }

private:
  std::size_t pc_ = 0;
  int acc_ = 0;
};

void load_program(const std::string &filename, Memory &mem) {
  std::ifstream fs{filename};
  for (std::string line; std::getline(fs, line);) {
    std::stringstream ss{line};
    std::string op;
    int value;
    ss >> op;
    if (op == "acc") {
      ss >> value;
      mem.add_instruction(Ops::ACC, value);
    } else if (op == "jmp") {
      ss >> value;
      mem.add_instruction(Ops::JMP, value);
    } else if (op == "nop") {
      ss >> value;
      mem.add_instruction(Ops::NOOP, value);
    }
  }
}

bool has_loop(CPU &cpu, Memory &mem) {
  // Solution-1
  std::set<std::size_t> ops_executed{};
  auto pc = cpu.pc();
  while (ops_executed.count(pc) == 0 && pc < mem.size()) {
    ops_executed.insert(pc);
    cpu.run_next(mem);
    pc = cpu.pc();
  }
  return ops_executed.count(pc) == 1;
}

int main(int argc, char **argv) {
  Memory mem{};
  CPU cpu{};
  load_program("input8.txt", mem);

  // Solution-1
  std::set<std::size_t> ops_executed{};
  std::vector<std::size_t> execution_order;

  auto pc = cpu.pc();
  while (ops_executed.count(pc) == 0) {
    execution_order.push_back(pc);
    ops_executed.insert(pc);
    cpu.run_next(mem);
    pc = cpu.pc();
  }
  std::cout << "Solution-1: " << cpu.accumulator() << std::endl;  

  // Solution-2: Iterate over the instructions executed until the loop was
  // detected, and flip 1 jmp/noop at a time until an execution without loops
  // is detected
  for (auto pc : execution_order) {
    cpu.reset();
    auto inst = mem.read(pc);
    if (inst.first == Ops::JMP) {
      mem.set(pc, Ops::NOOP, inst.second);
      if (!has_loop(cpu, mem)) {
        std::cout << "Solution-2: " << cpu.accumulator() << std::endl;
        return 0;
      }
      mem.set(pc, Ops::JMP, inst.second);
      continue;
    }

    if (inst.first == Ops::NOOP) {
      mem.set(pc, Ops::JMP, inst.second);
      if (!has_loop(cpu, mem)) {
        std::cout << "Solution-2: " << cpu.accumulator() << std::endl;
        return 0;
      }
      mem.set(pc, Ops::NOOP, inst.second);
      continue;
    }
  }
  return 1;
}
