#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  ifstream input("./4.txt");
  array<int, 213> times_to_repeat;
  times_to_repeat.fill(0);
  string line;
  int sum = 0;
  int num_cards = 0;
  int j = 0;
  while (std::getline(input, line)) {
    num_cards++;
    auto colon_pos = line.find(':');
    auto card_id = line.substr(0, colon_pos);
    line = line.erase(0, colon_pos + 1);

    auto bar_pos = line.find('|');
    auto winning_numbers = line.substr(0, bar_pos);
    auto my_numbers = line.erase(0, bar_pos + 1);

    stringstream winning_numbers_stream(winning_numbers);
    string num_str;
    vector<int> winning_numbers_vec;
    int i = 0;
    while (winning_numbers_stream >> num_str) {
      winning_numbers_vec.push_back(stoi(num_str));
      ++i;
    }

    stringstream my_numbers_stream(my_numbers);
    int points = 0;
    i = 0; // number of wins
    while (my_numbers_stream >> num_str)
      if (find(winning_numbers_vec.begin(), winning_numbers_vec.end(),
               stoi(num_str)) != std::end(winning_numbers_vec)) {
        if (i == 0)
          points = 1;
        else
          points *= 2;
        ++i;
      }

    for (int x = 0; x < times_to_repeat.at(j) + 1; ++x)
      for (int x = j + 1; x < j + i + 1; ++x)
        times_to_repeat[x] += 1;

    sum += points;
    ++j;
  }
  cout << sum << '\n';

  for (const auto num : times_to_repeat)
    num_cards += num;
  cout << num_cards << '\n';
}
