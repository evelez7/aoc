#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main(int argc, char **argv) {
  ifstream input("./6.txt");
  string timeLine;
  getline(input, timeLine);
  timeLine = timeLine.erase(0, 7);
  stringstream timeSS(timeLine);
  string time;
  int i = 0;
  array<int, 4> times;
  while (timeSS >> time) {
    times.at(i) = stoi(time);
    ++i;
  }

  string distanceLine;
  getline(input, distanceLine);
  timeLine = distanceLine.erase(0, 10);
  stringstream distanceSS(timeLine);
  string distance;
  i = 0;
  array<int, 4> distances;
  while (distanceSS >> distance) {
    distances.at(i) = stoi(distance);
    ++i;
  }

  int product = 1;
  for (int j = 0; j < 4; ++j) {
    int currentSpeed = 0;
    int count = 0;
    for (int k = 0; k < times.at(j); ++k) {
      if ((times.at(j) - k) * currentSpeed >= distances.at(j))
        ++count;
      currentSpeed += 1;
    }
    product *= count;
  }
  // part 2
  long bigDistance, bigTime;
  string bigTimeStr;
  for (const auto &timeT : times) {
    bigTimeStr.append(to_string(timeT));
  }
  bigTime = stol(bigTimeStr);

  string bigDistanceStr;
  for (const auto &distanceT : distances)
    bigDistanceStr.append(to_string(distanceT));

  bigDistance = stol(bigDistanceStr);
  int currentSpeed = 0;
  long count = 0;
  for (int j = 0; j < bigTime; ++j) {
    if ((bigTime - j) * currentSpeed >= bigDistance) {
      ++count;
    }
    currentSpeed += 1;
  }
  cout << product << '\n';
  cout << count << '\n';
  return 0;
}