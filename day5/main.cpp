#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

class Solution {
private:
  std::pair<unsigned long, unsigned long> getPair(std::string range) {
    int split = range.find('-');
    unsigned long low = std::stol(range.substr(0, split));
    unsigned long high = std::stol(range.substr(split + 1));
    return std::pair(low, high);
  }

public:
  int one(std::ifstream &in) {
    std::vector<std::pair<unsigned long, unsigned long>> ranges;

    int amount = 0;

    std::string inputString;
    while (getline(in, inputString)) {
      if (inputString.empty()) {
        break;
      }
      ranges.push_back(getPair(inputString));
    }

    while (getline(in, inputString)) {
      unsigned long inputNum = std::stol(inputString);
      for (auto [low, high] : ranges) {
        if (inputNum >= low && inputNum <= high) {
          amount++;
          break;
        }
      }
    }

    in.clear();
    in.seekg(0);
    return amount;
  }

  unsigned long two(std::ifstream &in) {
    std::vector<std::pair<unsigned long, unsigned long>> ranges;

    std::string inputString;
    while (getline(in, inputString)) {
      if (inputString.empty()) {
        break;
      }
      ranges.push_back(getPair(inputString));
    }

    std::sort(ranges.begin(), ranges.end());
    std::vector<std::pair<unsigned long, unsigned long>> mergedRanges;

    for (int i = ranges.size() - 1; i > 0; --i) {
      if (ranges[i].first <= ranges[i - 1].second) {
        ranges[i - 1].second = std::max(ranges[i].second, ranges[i - 1].second);
        ranges[i].first = 1;
        ranges[i].second = 0;
      }
    }

    unsigned long amount = 0;
    for (auto [low, high] : ranges) {
      amount += high - low + 1;
    }

    in.clear();
    in.seekg(0);
    return amount;
  }
};

int main() {
  Solution s;
  std::ifstream inFile("./input.txt");
  std::cout << s.one(inFile) << std::endl;
  std::cout << s.two(inFile) << std::endl;
  return 0;
}
