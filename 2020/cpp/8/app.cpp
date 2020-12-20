#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

enum class Ops {
  ACC,
  JMP,
  NOOP
};

class Memory {
 public:
  void add_instruction(Ops op_code, int value = 0) {
    mem_.push_back({op_code, value});
  }

  const std::pair<Ops, int>& read(std::size_t idx) const {
    return mem_.at(idx);
  }
  
 private:
  std::vector<std::pair<Ops, int>> mem_;
};

class CPU {
 public:
  void reset() {
    pc_ = 0;
    acc_ = 0;
   }

  int accumulator() {
    return acc_;
  }

  void run_next(const Memory& mem) {
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

  std::size_t pc() const {
    return pc_;
  }
  
 private:
  std::size_t pc_ = 0;
  int acc_ = 0;
};

void load_program(const std::string& filename, Memory& mem) {
  std::ifstream fs{filename};
  for (std::string line ; std::getline(fs, line) ; ) {
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
      mem.add_instruction(Ops::NOOP);      
    }
  }
}

int main(int argc, char** argv) {
  Memory mem{};
  CPU cpu{};
  load_program("input8.txt", mem);
  std::set<std::size_t> ops_executed{};
  auto pc = cpu.pc();
  while (ops_executed.count(pc) == 0) {
    ops_executed.insert(pc);
    cpu.run_next(mem);
    pc = cpu.pc();
  }

  std::cout << cpu.accumulator() << std::endl;
}
