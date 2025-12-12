#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <tuple>
#include <vector>

class Solution {
private:
  struct box {
    int x;
    int y;
    int z;

    int rank = 0;
    long count = 1;
    box *rep;

    box(int x, int y, int z) : rep(this), x(x), y(y), z(z) {}
  };

  box *findSet(box *x) {
    if (x->rep != x) {
      x->rep = findSet(x->rep);
    }
    return x->rep;
  }

  box *link(box *x, box *y) {
    if (x->rank > y->rank) {
      y->rep = x;
      x->count += y->count;
      return x;
    } else {
      x->rep = y;
      if (x->rank == y->rank) {
        y->rank++;
      }
      y->count += x->count;
      return y;
    }
  }

  struct connection {
    box *j1;
    box *j2;
    long distance;

    connection(box *j1, box *j2) : j1(j1), j2(j2) {
      int xdiff = j1->x - j2->x;
      int ydiff = j1->y - j2->y;
      int zdiff = j1->z - j2->z;
      distance = std::pow(xdiff, 2) + std::pow(ydiff, 2) + std::pow(zdiff, 2);
    };

    bool operator<(const connection &other) const {
      return distance < other.distance;
    }
  };

  std::tuple<int, int, int> splitXYZ(std::string &line) {
    int split1 = line.find(",");
    int x = std::stoi(line.substr(0, split1));
    int split2 = line.find(",", split1 + 1);
    int y = std::stoi(line.substr(split1 + 1, split2 - split1));
    int split3 = line.find(",", split2 + 1);
    int z = std::stoi(line.substr(split2 + 1, split3 - split2));
    return std::tuple(x, y, z);
  }

public:
  long one(std::ifstream &in) {
    std::list<box> junctions;

    std::string inString;
    while (std::getline(in, inString)) {
      auto [x, y, z] = splitXYZ(inString);
      junctions.emplace_back(x, y, z);
    }

    std::vector<connection> connections;
    for (auto it1 = junctions.begin(); it1 != --junctions.end(); ++it1) {
      for (auto it2 = it1; it2 != junctions.end(); ++it2) {
        connections.emplace_back(&(*it1), &(*it2));
      }
    }

    std::sort(connections.begin(), connections.end());

    std::vector<connection> selections;
    for (int i = 0, u = 1000; i < u; i++) {
      connection conn = connections[i];
      if (!conn.distance) {
        u++;
        continue;
      }

      if (findSet(conn.j1) != findSet(conn.j2)) {
        selections.push_back(conn);
        link(findSet(conn.j1), findSet(conn.j2));
      }
    }

    std::set<box *> reps;
    for (auto &conn : selections) {
      reps.insert(findSet(conn.j1));
    }

    std::vector<int> counts;
    for (auto &p : reps) {
      counts.push_back(p->count);
    }

    std::sort(counts.begin(), counts.end(), [](int a, int b) { return a > b; });

    in.clear();
    in.seekg(0);
    return counts[0] * counts[1] * counts[2];
  }

  long two(std::ifstream &in) {
    std::list<box> junctions;

    std::string inString;
    while (std::getline(in, inString)) {
      auto [x, y, z] = splitXYZ(inString);
      junctions.emplace_back(x, y, z);
    }

    std::vector<connection> connections;
    for (auto it1 = junctions.begin(); it1 != --junctions.end(); ++it1) {
      for (auto it2 = it1; it2 != junctions.end(); ++it2) {
        connections.emplace_back(&(*it1), &(*it2));
      }
    }

    std::sort(connections.begin(), connections.end());

    std::pair<int, int> lastX;
    int i = 0;
    int u = 0;
    while (i < 999) {
      connection conn = connections[u];
      if (conn.distance && findSet(conn.j1) != findSet(conn.j2)) {
        link(findSet(conn.j1), findSet(conn.j2));
        lastX = std::pair(conn.j1->x, conn.j2->x);
        i++;
      }
      u++;
    }

    in.clear();
    in.seekg(0);
    return (long)lastX.first * lastX.second;
  }
};

int main() {
  Solution s;
  std::ifstream inFile("./input.txt");
  std::cout << s.one(inFile) << std::endl;
  std::cout << s.two(inFile) << std::endl;
  return 0;
}
