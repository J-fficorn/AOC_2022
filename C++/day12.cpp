#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <climits>
#include <queue>
#include <array>
using namespace std;
ifstream fin("i");
bool part_one = true;
char height[1000][1000];
int dist[1000][1000], rows, cols,
    dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

class comp {
    public: bool operator()(array<int,3> a, array<int,3> b) {
        return a[2] < b[2];
    }
};

void djikstra(int start[2]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            dist[i][j] = (i == start[0] && j == start[1]) ? 0 : rows * cols + 1;
    priority_queue<array<int,3>, vector<array<int,3>>, comp> q;
    q.push({start[0], start[1], 0});
    while (!q.empty()) {
        int r = q.top()[0], c = q.top()[1], cur_dist = q.top()[2];
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || //out of bounds
               (tolower(height[nr][nc]) - '0') - 1 > (tolower(height[r][c]) - '0')) //traversable
                continue;
            if (cur_dist + 1 < dist[nr][nc]) {
                dist[nr][nc] = cur_dist + 1;
                q.push({nr, nc, dist[nr][nc]});
            }
        }
    }
}

int main() {
    auto time_start = chrono::steady_clock::now();
    string s;
    rows = 0, cols = 0;
    int start[2], end[2];
    while (getline(fin, s)) {
        for (cols = 0; cols < s.size(); cols++) {
            height[rows][cols] = s.at(cols);
            switch (height[rows][cols]) {
                case 'S':
                    start[0] = rows; start[1] = cols;
                    height[rows][cols] = 'a';
                    break;
                case 'E':
                    end[0] = rows; end[1] = cols;
                    height[rows][cols] = 'z';
                    break;
            }
        } 
        rows++;
    } //create height arr
    djikstra(start);
    int min_traversal = dist[end[0]][end[1]];
    if (!part_one)
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < 3; j++)
                if (height[i][j] == 'a') {
                    start[0] = i; start[1] = 2;
                    djikstra(start);
                    min_traversal = min(min_traversal, dist[end[0]][end[1]]);
                }
    cout << min_traversal;
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    printf("\n%d ms\n", time_elapsed.count());
    return 0;
}
