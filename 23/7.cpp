#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

map<char, int> strengths{{'A', 12}, {'K', 11}, {'Q', 10}, {'J', 9}, {'T', 8},
                         {'9', 7},  {'8', 6},  {'7', 5},  {'6', 4}, {'5', 3},
                         {'4', 2},  {'3', 1},  {'2', 0}};

int determineHand(string hand) {
  vector<int> cards(13);
  fill(cards.begin(), cards.end(), 0);
  for (const auto &card : hand) {
    switch (card) {
    case 'A':
      cards[12]++;
      break;
    case 'K':
      cards[11]++;
      break;
    case 'Q':
      cards[10]++;
      break;
    case 'J':
      cards[9]++;
      break;
    case 'T':
      cards[8]++;
      break;
    case '9':
      cards[7]++;
      break;
    case '8':
      cards[6]++;
      break;
    case '7':
      cards[5]++;
      break;
    case '6':
      cards[4]++;
      break;
    case '5':
      cards[3]++;
      break;
    case '4':
      cards[2]++;
      break;
    case '3':
      cards[1]++;
      break;
    case '2':
      cards[0]++;
      break;
    default:
      cout << "Invalid card" << card << "\n";
      // exit(-1);
      break;
    }
  }
  int score = 0;
  for (int i = 0; i < 13; ++i) {
    auto maxIt = max_element(cards.begin(), cards.end());
    while (maxIt != cards.end()) {
      switch (*maxIt) {
      case 1:
        score += 1;
        maxIt = cards.end();
        break;
      case 2:
        score += 2;
        if (score == 2) {
          maxIt = cards.end(); // no double two pair anyways
        }
        break;
      case 3:
        score += 3;
        maxIt++; // might be a full house
        break;
      // make sure the rest are worth more than a full house
      case 4:
        score += 6;
        maxIt = cards.end();
        break;
      case 5:
        score += 7;
        maxIt = cards.end();
        break;
      }
    }
  }
  return score;
}

int main(int argc, char **argv) {
  ifstream input("7.txt");
  string line;
  vector<pair<string, int>> bucket5;
  vector<pair<string, int>> bucket4;
  vector<pair<string, int>> bucket3;
  vector<pair<string, int>> bucket2;
  vector<pair<string, int>> bucket1;
  // wanted to use multimap, got lazy
  while (getline(input, line)) {
    stringstream ss(line);
    string hand;
    long bid;
    string empty;
    string bidStr;
    ss >> hand >> bidStr;
    bid = stoi(bidStr);
    int val = determineHand(hand);
    if (val == 1) {
      bucket1.push_back({hand, bid});
    } else if (val == 2) {
      bucket2.push_back({hand, bid});
    } else if (val == 3) {
      bucket3.push_back({hand, bid});
    } else if (val == 6) {
      bucket4.push_back({hand, bid});
    } else if (val == 7) {
      bucket5.push_back({hand, bid});
    }
  }

  vector<int> wagers;
  auto sortCB = [](const auto &a, const auto &b) {
    for (int i = 0; i < 6; ++i) {
      if (strengths.at(a.first[i]) > strengths.at(b.first[i]))
        return true;
      else if (strengths.at(a.first[i]) < strengths.at(b.first[i]))
        return false;
    }
    return false;
  };
  sort(bucket1.begin(), bucket1.end(), sortCB);
  sort(bucket2.begin(), bucket2.end(), sortCB);
  sort(bucket3.begin(), bucket3.end(), sortCB);
  sort(bucket4.begin(), bucket4.end(), sortCB);
  sort(bucket5.begin(), bucket5.end(), sortCB);
  long sum = 0;
  cout << "size: " << wagers.size() << '\n';
  for (int i = 0; i < wagers.size(); ++i) {
    sum += wagers.at(i) * (i + 1);
  }
  cout << sum << '\n';
}
