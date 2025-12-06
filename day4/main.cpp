#include <fstream>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

class Solution {
private:
  // Make grid with padding = 1.
  std::vector<std::vector<int>> computeGrid(std::ifstream &inFile) {
    std::vector<std::vector<int>> grid;
    std::vector<int> empty;
    std::string input;
    std::getline(inFile, input);

    for (int i = 0, u = input.size(); i < u + 2; ++i)
      empty.push_back(-1);
    grid.push_back(empty);

    inFile.clear();
    inFile.seekg(0);

    while (std::getline(inFile, input)) {
      std::vector<int> row;

      row.push_back(-1);
      for (int i = 1, u = input.length() + 1; i < u; ++i) {
        if (input[i - 1] == '.') {
          row.push_back(-1);
          continue;
        }

        int curr = 0;
        int set = 0;

        set = row[i - 1] >= 0;
        curr += set;
        row[i - 1] += set;

        std::vector<int> &prevRow = grid[grid.size() - 1];

        for (int x = 0; x < 3; x++) {
          set = (prevRow[i + 1 - x] >= 0);
          curr += set;
          prevRow[i + 1 - x] += set;
        }

        row.push_back(curr);
      };
      row.push_back(-1);
      grid.push_back(row);
    }

    grid.push_back(empty);

    return grid;
  };

public:
  int rollsAvaliable(std::ifstream &in) {
    std::vector<std::vector<int>> grid = computeGrid(in);

    int avaliable = 0;

    for (auto row : grid) {
      for (auto num : row) {
        if (num < 0) {
          std::cout << ".";
        } else if (num < 4) {
          std::cout << "X";
          avaliable++;
        } else {
          std::cout << "@";
        }
      }
      std::cout << std::endl;
    }
    return avaliable;
  }

  // Should be O(n**2)
  int rollsRemovable(std::ifstream &in) {
    std::vector<std::vector<int>> grid = computeGrid(in);
    std::stack<std::pair<int, int>> stack;

    int removed = 0;

    // Add all to stack.
    for (int row = 1, height = grid.size() - 1; row < height; ++row) {
      for (int column = 1, width = grid[0].size() - 1; column < width;
           ++column) {
        int num = grid[row][column];
        stack.push(std::pair(row, column));
      }
    }

    // Check every roll and if removable recheck all neighbors
    while (!stack.empty()) {
      auto [row, column] = stack.top();
      stack.pop();

      int num = grid[row][column];
      if (num >= 0 && num < 4) {
        removed++;

        grid[row][column] = -1;
        grid[row][column - 1]--;
        grid[row][column + 1]--;
        stack.push(std::pair(row, column + 1));
        stack.push(std::pair(row, column - 1));

        for (int x = 0; x < 3; x++) {
          grid[row + 1][column - 1 + x]--;
          grid[row - 1][column - 1 + x]--;
          stack.push(std::pair(row + 1, column - 1 + x));
          stack.push(std::pair(row - 1, column - 1 + x));
        }
      }
    }

    return removed;
  };
};

int main() {
  Solution s;

  std::ifstream stream("./input.txt");
  std::cout << s.rollsRemovable(stream) << std::endl;
  return 0;
}
