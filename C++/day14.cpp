#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
bool cave_visited[1500][1500];
int r_max = 0, dc[3] = {0, -1, 1};

bool dfs(int r, int c) {
    // cout << r << " " << c << endl;
    if ((part_one && r >= r_max) ||
       (!part_one && cave_visited[0][500])) return false;
    for (int i = 0; i < 3; i++)
        if (!cave_visited[r + 1][c + dc[i]])
            return dfs(r + 1, c + dc[i]);
    cave_visited[r][c] = true;
    return true;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, u;
    int n = 0, instructions[15][2]; //[0] -> r, [1] -> c
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ' ')) {
            if (n % 2 == 0) {
                ss y(t);
                int m = 0;
                while (getline(y, u, ','))
                    instructions[n / 2][m++] = stoi(u);
            }
            n++;
        }
        for (int i = 1; i < n / 2 + 1; i++) {
            r_max = max(r_max, instructions[i][1]);
            if (instructions[i][0] != instructions[i - 1][0]) {
                int bottom = min(instructions[i][0], instructions[i - 1][0]),
                    top = max(instructions[i][0], instructions[i - 1][0]);
                for (int j = bottom; j <= top; j++)
                    cave_visited[instructions[i][1]][j] = true;
            } else {
                int bottom = min(instructions[i][1], instructions[i - 1][1]),
                    top = max(instructions[i][1], instructions[i - 1][1]);
                for (int j = bottom; j <= top; j++)
                    cave_visited[j][instructions[i][0]] = true;
            }
        }
        n = 0;
    } //double checked
    int sand = 0;
    if (!part_one)
        for (int i = 0; i < 1000; i++)
            cave_visited[r_max + 2][i] = true;
    while (dfs(0, 500))
        sand++;
    cout << sand;
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start);
    printf("\n%.2f ms\n", elapsed.count()*1e-6);
    return 0;
}
