#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>
#define MAXN 100+2
using namespace std;
ifstream fin("i");
bool part_one = false;
int heights[MAXN][MAXN], views[MAXN][MAXN][5], total_rows = 0, total_cols;

void find_views(int r, int c) {
    bool scenic[4]; fill_n(scenic, 4, true);
    for (int i = r - 1; i >= 0; i--) { //top
        if (scenic[0]) views[r][c][0]++;
        if (heights[i][c] >= heights[r][c])
            scenic[0] = false;
    }
    for (int i = r + 1; i < total_rows; i++) { //bot
        if (scenic[1]) views[r][c][1]++;
        if (heights[i][c] >= heights[r][c])
            scenic[1] = false;
    }
    for (int i = c - 1; i >= 0; i--) { //left
        if (scenic[2]) views[r][c][2]++;
        if (heights[r][i] >= heights[r][c])
            scenic[2] = false;
    }
    for (int i = c + 1; i < total_cols; i++) { //right
        if (scenic[3]) views[r][c][3]++;
        if (heights[r][i] >= heights[r][c])
            scenic[3] = false;
    }
    for (bool x : scenic) if (x) views[r][c][4] = 1;
}

int main() {
    auto time_start = chrono::steady_clock::now();
    string s;
    while (fin >> s) {
        total_cols = s.length();
        for (int i = 0; i < total_cols; i++)
            heights[total_rows][i] = s.at(i) - '0';
        total_rows++;
    }
    for (int i = 0; i < total_rows; i++)
        for (int j = 0; j < total_cols; j++)
            find_views(i, j);
    int scenery_trees = 0;
    for (int i = 0; i < total_rows; i++)
        for (int j = 0; j < total_cols; j++)
            if (part_one) {
                if (views[i][j][4]) scenery_trees++;
            } else {
                int temp_scenery = 1;
                for (int k = 0; k < 4; k++)
                    temp_scenery *= views[i][j][k];
                scenery_trees = max(scenery_trees, temp_scenery);
            }
    cout << scenery_trees;   
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    cout << endl << time_elapsed.count() << " ms" << endl;
    return 0;
}
