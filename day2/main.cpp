#include <cmath>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <set>
#include <string>
#include <utility>
#include <vector>

class solution {
private:
  std::pair<std::string, std::string> getStartEndString(std::string in) {
    int split = in.find('-');
    std::string start = in.substr(0, split);
    std::string end = in.substr(split + 1);

    if (end[end.length() - 1] == '\n') {
      end.pop_back();
    }

    return std::pair(start, end);
  }

  void one(unsigned long start, unsigned long end, int n, unsigned long &sum) {
    if (n % 2) {
      return;
    }

    unsigned long upperStart = start * std::pow(10, -(n / 2));
    unsigned long upperEnd = end * std::pow(10, -(n / 2));

    while (upperStart <= upperEnd) {
      unsigned long temp = upperStart * std::pow(10, n / 2) + upperStart;
      std::cout << temp << std::endl;
      if (temp <= end && start <= temp) {
        sum += temp;
      }
      upperStart++;
    }
  }

  void two(unsigned long start, unsigned long end, int n, unsigned long &sum) {
    std::vector<int> factors;
    for (int i = 1; i <= n / 2; ++i) {
      if (n % i == 0) {
        factors.push_back(i);
      }
    }

    std::set<unsigned long> nums;
    for (auto fact : factors) {
      unsigned long upperStart = start * std::pow(10, (fact - n));
      unsigned long upperEnd = end * std::pow(10, (fact - n));

      while (upperStart <= upperEnd) {
        unsigned long temp = upperStart;
        for (int i = 1; i < n / fact; ++i) {
          temp *= std::pow(10, fact);
          temp += upperStart;
        }
        if (temp <= end && start <= temp) {
          nums.insert(temp);
        }
        upperStart++;
      }
    }

    for (auto num : nums) {
      std::cout << num << std::endl;
      sum += num;
    }
  }

  void bruteTwo(unsigned long istart, unsigned long iend, unsigned long &sum) {
    while (istart <= iend) {
      std::string start = std::to_string(istart);
      for (int i = 2, u = start.length(); i <= u; ++i) {
        if (start.length() % i != 0) {
          continue;
        }

        long segSize = start.length() / i;
        std::string segment = start.substr(0, segSize);
        bool match = true;

        for (int y = 1, x = i; y < x; ++y) {
          if (start.substr(y * segSize, segSize) != segment) {
            match = false;
            break;
          }
        }

        if (match) {
          sum += istart;
          break;
        }
      }
      istart++;
    }
  }

public:
  unsigned long invalidIdSum(std::ifstream &input) {
    unsigned long sum = 0;

    std::string in;
    while (std::getline(input, in, ',')) {
      auto [start, end] = getStartEndString(in);

      if (start.length() < end.length()) {
        std::string start1(end.length(), '0');
        std::string end1(start.length(), '9');
        start1.replace(0, 1, 1, '1');

        // bruteTwo(std::stol(start), std::stol(end1), sum);
        // bruteTwo(std::stol(start1), std::stol(end), sum);

        two(std::stol(start), std::stol(end1), start.length(), sum);
        two(std::stol(start1), std::stol(end), end.length(), sum);
      } else {
        // bruteTwo(std::stol(start), std::stol(end), sum);

        two(std::stol(start), std::stol(end), start.length(), sum);
      }
    }

    return sum;
  }
};

int main() {
  solution s;
  std::ifstream input("./input.txt");
  std::cout << s.invalidIdSum(input) << std::endl;
}
