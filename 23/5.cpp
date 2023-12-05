#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  bool part1 = false; // im tired
  ifstream input("./5.txt");
  string seedsLine;
  getline(input, seedsLine);
  seedsLine = seedsLine.erase(0, seedsLine.find(":") + 1);
  stringstream seedsLineStream(seedsLine);
  string seed_str;
  vector<vector<long>> categoryID;
  categoryID.resize(9);
  while (seedsLineStream >> seed_str)
    categoryID.at(0).push_back(stol(seed_str));

  for (int i = 1; i < categoryID.size(); ++i) {
    categoryID.at(i).resize(categoryID.at(0).size());
    fill(categoryID.at(i).begin(), categoryID.at(i).end(), -1);
  }

  string line;
  // dest, source, length
  bool parsingPairs = false;
  int categories = 1;
  while (getline(input, line)) {
    if (line.size() == 0) {
      parsingPairs = false;
      continue;
    }

    if (parsingPairs) {
      stringstream lineStream(line);
      string num;
      int index = 0;
      long dest, source, length;
      while (lineStream >> num) {
        if (index == 0) {
          dest = stol(num);
        } else if (index == 1) {
          source = stol(num);
        } else if (index == 2) {
          length = stol(num);
        }
        ++index;
      }

      for (int i = 0; i < categoryID.at(categories - 1).size(); ++i) {
        if (categoryID.at(categories - 1).at(i) >= source &&
            categoryID.at(categories - 1).at(i) <= source + length) {
          int offset = categoryID.at(categories - 1).at(i) - source;
          categoryID.at(categories).at(i) = dest + offset;
        }
      }
    }

    if (isalpha(line.at(0))) {
      for (int i = 0; i < categoryID.at(categories).size(); ++i) {
        if (categoryID.at(categories).at(i) == -1) {
          categoryID.at(categories).at(i) = categoryID.at(categories - 1).at(i);
        }
      }

      parsingPairs = true;
      categories++;
    }
  }

  int lowest = INT_MAX;
  for (const auto &loc : categoryID.at(categories)) {
    if (loc < lowest) {
      lowest = loc;
    }
  }
  cout << lowest << '\n';
  return 0;
}
