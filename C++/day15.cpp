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

constexpr inline bool in_bounds(int a, int upper) {
    return a >= 0 && a <= upper;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, input[10];
    int n = 0, input_n = 0; //[0] minx, [1] maxx, [2] miny, [3] maxy;
    int x, y, b_x, b_y;
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ' '))
            input[input_n++] = t;
        sensor temp_sensor = {stoi(input[2].substr(2, input[2].size() - 1 - 2)),
                            stoi(input[3].substr(2, input[3].size() - 1 - 2)),
                            stoi(input[8].substr(2, input[8].size() - 1 - 2)),
                            stoi(input[9].substr(2))};
        temp_sensor.man_dist = abs(temp_sensor.x - temp_sensor.b_x) + abs(temp_sensor.y - temp_sensor.b_y);
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
            // printf("%d: %d, %d, %d\n", i, cur_sensor.x, cur_sensor.x - radius, cur_sensor.x + radius);
        }
        sort(ranges.begin(), ranges.end());
        pair<int, int> range = ranges[0];
        for (int i = 1; i < ranges.size(); i++) {
            if (ranges[i].second < range.first) {
                total_range += range.second - range.first + 1;
                range.first = ranges[i].first; range.second = ranges[i].second;
                continue;
            } else if (ranges[i].first > range.second) {
                total_range += range.second - range.first + 1;
                range.first = ranges[i].first; range.second = ranges[i].second;
                continue;
            }
            range.first = min(range.first, ranges[i].first);
            range.second = max(range.second, ranges[i].second);
        }
        total_range += range.second - range.first + 1 - beacons_in_line.size();
    } else {
        int upper = 4000000;
        vector<pair<int, int>> possible_locations;
        for (int i = 0; i < n; i++) {
            sensor ssr = all_sensors[i];
            int new_man = ssr.man_dist + 1;
            for (int j = new_man; j >= 0; j--) {
                int l_x = ssr.x - (new_man - j), r_x = ssr.x + (new_man - j),
                    t_y = ssr.y + j, b_y = ssr.y - j;
                if (in_bounds(l_x, upper)) {
                    if (in_bounds(t_y, upper)) possible_locations.push_back(make_pair(l_x, t_y));
                    if (in_bounds(b_y, upper)) possible_locations.push_back(make_pair(l_x, b_y));
                }
                if (in_bounds(r_x, upper)) {
                    if (in_bounds(t_y, upper)) possible_locations.push_back(make_pair(r_x, t_y));
                    if (in_bounds(b_y, upper)) possible_locations.push_back(make_pair(r_x, b_y));
                }
            }
            //trace man + 1
        }
        for (int i = 0; i < possible_locations.size(); i++) {
            bool valid = true;
            for (int j = 0; j < n; j++) {
                sensor cur_sensor = all_sensors[j];
                int cur_man_dist = abs(cur_sensor.x - possible_locations[i].first)
                                 + abs(cur_sensor.y - possible_locations[i].second);
                if (cur_sensor.man_dist >= cur_man_dist) valid = false;
            }
            if (valid)
                total_range = 4000000 * ((long) possible_locations[i].first) + possible_locations[i].second;
        }
    }
    cout << total_range;
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start);
    printf("\n%.2f ms\n", elapsed.count()*1e-6);
    return 0;
}
