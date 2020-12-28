#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

namespace {
enum class DIR { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

enum class ACTION { NORTH, EAST, SOUTH, WEST, RLEFT, RRIGHT, FWD, NOOP };

DIR from_int(int dir) { return static_cast<DIR>(dir); }

class Vehicle {
private:
  // Rotate right 90 degrees
  void rotate_plus() {
    int dir = static_cast<int>(dir_);
    dir_ = from_int((dir + 1) % 4);
  }

  // Rotate left 90 degrees
  void rotate_minus() {
    int dir = static_cast<int>(dir_);
    dir = (dir == 0) ? 3 : (dir - 1);
    dir_ = from_int(dir);
  }

private:
  // The pose of the car includes the direction it is pointing
  // and the x,y coordinates
  DIR dir_ = DIR::EAST;
  std::size_t posx_ = 0, posy_ = 0;

public:
  // Apply action unit times. Notice that for Left and Right rotations
  // the units is expected to be a multiple of 90
  void update(ACTION action, std::size_t units) {
    // Delta x,y that will be applied to the position
    int dx = 0;
    int dy = 0;
    switch (action) {
    case ACTION::NORTH:
      dy = -units;
      break;
    case ACTION::SOUTH:
      dy = units;
      break;
    case ACTION::EAST:
      dx = units;
      break;
    case ACTION::WEST:
      dx = -units;
      break;
    case ACTION::RLEFT:
      for (auto i = 0U; i < units / 90; ++i) {
        rotate_minus();
      }
      break;
    case ACTION::RRIGHT:
      for (auto i = 0U; i < units / 90; ++i) {
        rotate_plus();
      }
      break;
    case ACTION::FWD: {
      // For the forward action we need to consider the direction
      // the vehicle is pointing to
      switch (dir_) {
      case DIR::NORTH:
        update(ACTION::NORTH, units);
        break;
      case DIR::SOUTH:
        update(ACTION::SOUTH, units);
        break;
      case DIR::EAST:
        update(ACTION::EAST, units);
        break;
      case DIR::WEST:
        update(ACTION::WEST, units);
        break;
      }
    }
    default:
      break;
    }
    posx_ += dx;
    posy_ += dy;
  }

  int getx() const { return posx_; }
  int gety() const { return posy_; }
};

// Parse a line of text and produce a pair<action, units>
std::pair<ACTION, int> get_action_units(const std::string &str) {
  int units = std::stoi(str.substr(1));
  switch (str[0]) {
  case 'N':
    return {ACTION::NORTH, units};
  case 'S':
    return {ACTION::SOUTH, units};
  case 'E':
    return {ACTION::EAST, units};
  case 'W':
    return {ACTION::WEST, units};
  case 'L':
    return {ACTION::RLEFT, units};
  case 'R':
    return {ACTION::RRIGHT, units};
  case 'F':
    return {ACTION::FWD, units};
  default:
    return {ACTION::NOOP, 0};
  }
}

} // anonymous namespace

int main(int argc, char *argv[]) {
  std::ifstream fs{"input12.txt"};
  Vehicle boat;
  for (std::string line; std::getline(fs, line);) {
    auto p = get_action_units(line);
    boat.update(p.first, p.second);
  }
  std::cout << (std::abs(boat.getx()) + std::abs(boat.gety())) << std::endl;
  return 0;
}
