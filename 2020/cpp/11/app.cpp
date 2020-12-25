#include <algorithm>
#include <bits/c++config.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

namespace {
/*! \brief The possible states of a cell
 */
enum class Cell { FLOOR, FREE, TAKEN };

/*! \brief A Map is a grid of Cell states stored as a vector in row major order
 */
class Map {
public:
  Map() = default;
  Map(Map &&map) = default;

  // Maps are not copiable
  Map(const Map &) = delete;

  /*! \brief Add a row to the map
   *
   * The number of colums is deduced from the first insertion, and must be the
   * same for all the rows
   */
  void add_row(const std::vector<Cell> &row) {
    // Set and/or check the number of columns
    if (cols_ == 0) {
      cols_ = row.size();
    } else {
      assert(row.size() == cols_ &&
             "All columns must have the same number of rows");
    }

    std::copy(row.begin(), row.end(), std::back_inserter(map_));
    ++rows_;
  }

  /*! \brief Set the state of a particular cell */
  void set(std::size_t row, std::size_t col, Cell value) {
    map_[row * cols_ + col] = value;
  }

  /*! \brief Get the state of a particular cell */
  Cell get(std::size_t row, std::size_t col) const {
    return map_[row * cols_ + col];
  }

  /*! \brief Get the state of the 8 neighbors of a particular cell
   *
   * Here we just return a list of Cell states. From this list is not
   * possible to determine the coordinates of each neightbor
   */
  std::vector<Cell> neighbors(std::size_t row, std::size_t col) const {
    std::vector<Cell> neighbors{};
    for (auto r = -1; r <= 1; ++r) {
      const auto target_row = row + r;
      if (target_row < 0 || target_row >= rows_) {
        continue;
      }
      for (auto c = -1; c <= 1; ++c) {
        const auto target_col = col + c;
        if (target_col < 0 || target_col >= cols_) {
          continue;
        }
        // Do not add the cell itself to the neighbors list
        if (r == 0 && c == 0) {
          continue;
        }
        neighbors.push_back(map_[target_row * cols_ + target_col]);
      }
    }
    return neighbors;
  }

  /*! \brief Count the number of cells in the mat with a particular state */
  std::size_t count(Cell state) {
    return std::count_if(map_.begin(), map_.end(),
                         [state](auto n) { return n == state; });
  }
  /*! \brief The number of rows */
  std::size_t rows() const { return rows_; }
  /*! \brief The number of cols */
  std::size_t cols() const { return cols_; }

private:
  std::vector<Cell> map_;
  std::size_t rows_;
  std::size_t cols_;
};

Map load_map(std::string filename) {
  std::ifstream fs{filename};
  Map m{};
  for (std::string line; std::getline(fs, line);) {
    std::vector<Cell> row{};
    for (const char c : line) {
      switch (c) {
      case 'L':
        row.push_back(Cell::FREE);
        break;
      case '.':
        row.push_back(Cell::FLOOR);
        break;
      case '#':
        row.push_back(Cell::TAKEN);
        break;
      }
    }
    m.add_row(row);
  }
  return m;
}

std::size_t update(Map &m) {
  std::vector<std::tuple<std::size_t, std::size_t, Cell>> changelist;
  for (auto row = 0; row < m.rows(); ++row) {
    for (auto col = 0; col < m.cols(); ++col) {
      const auto neighbors = m.neighbors(row, col);
      if (m.get(row, col) == Cell::FREE) {
        if (std::all_of(neighbors.begin(), neighbors.end(),
                        [](auto n) { return n != Cell::TAKEN; })) {
          changelist.push_back({row, col, Cell::TAKEN});
        }
      } else if (m.get(row, col) == Cell::TAKEN) {
        if (std::count_if(neighbors.begin(), neighbors.end(),
                          [](auto n) { return n == Cell::TAKEN; }) > 3) {
          changelist.push_back({row, col, Cell::FREE});
        }
      }
    }
  }
  for (auto &tuple : changelist) {
    m.set(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
  }
  return changelist.size();
}

} // namespace
int main(int argc, char *argv[]) {
  std::cout << "AdventOfCode2020 Day11" << std::endl;
  Map m{load_map("input11.txt")};
  std::cout << "Map loaded, rows: " << m.rows() << ", cols: " << m.cols()
            << std::endl;
  std::size_t updates = 0;
  while (update(m) > 0) {
    ++updates;
    // std::cout << "Updating more" << std::endl;
  }

  std::cout << "Part-1: " << updates << " updates" << std::endl;
  std::cout << "Part-1: " << m.count(Cell::TAKEN) << " occuppied cells"
            << std::endl;
  return 0;
}
