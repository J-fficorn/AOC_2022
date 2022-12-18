#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstring>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
struct valve {
    string name;
    int rate;
    vector<string> adj_names;
    vector<int> adj;
} scan[60];
struct pressure {
    int cur_rate = -1,
        value = 0;
    vector<int> opened_caves,
                times;
} dp[31][60];

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, input[20];
    int n = 0, input_n = 0;
    while (getline(fin, s)) {
        ss line(s);
        while (getline(line, t, ' '))
            input[input_n++] = t;
        valve v = {input[1],
                   stoi(input[4].substr(5, input[4].size() - 6))};
        for (int i = 9; i < input_n; i++)
            v.adj_names.push_back(input[i].substr(0, 2));
        scan[n] = v;
        input_n = 0;
        n++;
    } //
    sort(scan, scan + n, [](valve a, valve b) -> bool
        {return strcmp(a.name.c_str(), b.name.c_str()) < 0;}); //place AA first
    for (int i = 0; i < n; i++) {
        for (string s : scan[i].adj_names)
            for (int j = 0; j < n; j++)
                if (s == scan[j].name) scan[i].adj.push_back(j); //convert names to ints for easier ref
    }
    dp[0][0] = {0, 0}; //0 pressure @ time 0 @ valve A
    for (int i = 1; i <= 30; i++) {
        for (int j = 0; j < n; j++) {
            valve c = scan[j];
            pressure n_dp = dp[i - 1][j];
            if (n_dp.cur_rate >= 0) {
                bool opened = false;
                for (auto x : dp[i - 1][j].opened_caves)
                    if (x == j) opened = true;
                //visited & not opened
                if (!opened) {
                    n_dp.cur_rate += scan[j].rate; //open
                    n_dp.opened_caves.push_back(j); //add to its q
                    n_dp.times.push_back(i + 1);
                }
            }
            for (int k = 0; k < c.adj.size(); k++) //if any of its linked caves have a higher value
                if (dp[i - 1][c.adj[k]].cur_rate > n_dp.cur_rate)
                    n_dp = dp[i - 1][c.adj[k]]; //move
                //cant move + add in one
            n_dp.value += n_dp.cur_rate;
            dp[i][j] = n_dp;
        } //
    } //
    vector<pressure> vals;
    for (int i = 0; i < n; i++)
        vals.push_back(dp[30][i]);
    sort(vals.begin(), vals.end(), [](pressure a, pressure b) -> bool {return a.value > b.value;});
    cout << vals[0].value << endl;
    for (int s : vals[0].opened_caves)
        cout << scan[s].name << " ";
    cout << endl;
    for (int t : vals[0].times)
        cout << t << " ";
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start);
    printf("\n%.4f ms\n", elapsed.count()*1e-6);
    return 0;
}
