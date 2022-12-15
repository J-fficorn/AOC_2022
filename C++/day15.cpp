#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <unordered_set>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = true;
struct sensor {
    int x, y,
    b_x, b_y,
    man_dist;
};
vector<sensor> all_sensors;
vector<pair<int, int>> ranges;
unordered_set<int> beacons_in_line;
unordered_set<long> a, b;

constexpr inline bool in_bounds(int a, int upper) { return a >= 0 && a <= upper; }

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, input[10];
    int n = 0, input_n = 0;
    int x, y, b_x, b_y;
    while (getline(fin, s)) {
        ss line(s);
        while (getline(line, t, ' '))
            input[input_n++] = t;
        int x = stoi(input[2].substr(2, input[2].size() - 1 - 2)),
            y = stoi(input[3].substr(2, input[3].size() - 1 - 2)),
            b_x = stoi(input[8].substr(2, input[8].size() - 1 - 2)),
            b_y = stoi(input[9].substr(2)),
            md = abs(x - b_x) + abs(y - b_y);
        sensor temp_sensor = {x, y, b_x, b_y, md};
        a.insert(y - x + md + 1);
        a.insert(y - x - (md + 1)); //pos
        b.insert(y + x + md + 1);
        b.insert(y + x - (md + 1)); //neg
        all_sensors.push_back(temp_sensor);
        input_n = 0;
        n++;
    } //
    long total_range = 0;
    if (part_one) {
        int row = 2000000;
        for (int i = 0; i < n; i++) {
            sensor cur_sensor = all_sensors[i];
            int radius = cur_sensor.man_dist - abs(cur_sensor.y - row);
            if (radius < 0) continue;
            if (cur_sensor.b_y == row)
                beacons_in_line.insert(cur_sensor.b_x);
            ranges.push_back(make_pair(cur_sensor.x - radius, cur_sensor.x + radius));
        }
        sort(ranges.begin(), ranges.end());
        pair<int, int> range = ranges[0];
        for (int i = 1; i < ranges.size(); i++) {
            if (ranges[i].second < range.first || ranges[i].first > range.second) {
                total_range += range.second - range.first + 1;
                range = ranges[i];
                continue;
            }
            range = make_pair(min(range.first, ranges[i].first), max(range.second, ranges[i].second));
        }
        total_range += range.second - range.first + 1 - beacons_in_line.size();
    } else {
        int upper = 4000000;
        vector<pair<int, int>> possible_locations;
        for (auto s_a : a) {
            for (auto s_b : b) {
                int x = (s_b - s_a) / 2, y = (s_b + s_a) / 2;
                if (in_bounds(x, upper) && in_bounds(y, upper))
                    possible_locations.push_back(make_pair(x, y));
            }
        }
        for (auto p : possible_locations) {
            bool valid = true;
            for (auto ssr : all_sensors)
                if (ssr.man_dist >= (abs(ssr.x - p.first) + abs(ssr.y - p.second)))
                    valid = false;
            if (valid) total_range = 4000000 * (long) p.first + p.second;
        }
    }
    cout << total_range;
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start);
    printf("\n%.4f ms\n", elapsed.count()*1e-6);
    return 0;
}
