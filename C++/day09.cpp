#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <sstream>
#define pii pair<int, int>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false, visited[1000][1000];

bool segment_goes(pii a, pii b) {
    return abs(a.first - b.first) > 1 || abs(a.second - b.second) > 1;
}

int move_segment(int a, int b) {
    return a == b ? 0 : (a > b ? 1 : -1);
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, cmd[2];
    int length = part_one ? 2 : 10;
    vector<pii> rope(length, make_pair(0, 0));
    unordered_set<int> visited;
    int n = 0;
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ' '))
            cmd[n++] = t;
        n = 0;
        char dir = cmd[0].at(0);
        int mag = stoi(cmd[1]);
        for (int i = 0; i < mag; i++) {
            switch (dir) {
                case 'R':
                    rope[0].first++; break;
                case 'L':
                    rope[0].first--; break;
                case 'U':
                    rope[0].second++; break; //x y
                case 'D':
                    rope[0].second--; break;
            }
            for (int j = 1; j < length && segment_goes(rope[j - 1], rope[j]); j++) {
                rope[j].first += move_segment(rope[j - 1].first, rope[j].first);
                rope[j].second += move_segment(rope[j - 1].second, rope[j].second);
            }
            visited.insert(1000 * rope.back().first + rope.back().second);
        }
    }
    cout << visited.size();
    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << endl << elapsed.count() * 1e-9 << " ns" << endl;
    return 0;
}
