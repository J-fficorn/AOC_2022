#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>
#define MAXN 1000
#define OFFSET 300
#define ROUNDS 10
using namespace std;
ifstream fin("i");
bool part_one = false;
struct coord {
    bool has_elf, proposed, can_move; //has elf, elf has proposed to move here, elf can move here
    int prev[2]; //(elf to move, elf moved from)
} ground[MAXN][MAXN] = {0, 0, 0};
int directions[4] = {0, 1, 2, 3}, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0}, bounds[4] = {MAXN, 0, MAXN, 0}; //N, S, W, E

bool can_move(int dir, int y, int x) {
    if (dir == 0 || dir == 1) {
        for (int i = x - 1; i <= x + 1; i++)
            if (ground[y][i].has_elf) return false;
    } else { 
        for (int i = y - 1; i <= y + 1; i++)
            if (ground[i][x].has_elf) return false;
    }
    return true;
} //N S W E

void propose_loc(int y, int x) {
    for (int k = 0; k < 4; k++) {
        int dir = directions[k], ny = y + dy[dir], nx = x + dx[dir];
        if (can_move(dir, ny, nx)) {
            ground[ny][nx] = {0, true, !ground[ny][nx].proposed, {y, x}};
            return;
        }
    }
} //

void define_bounds(int i, int j) {
    bounds[0] = min(bounds[0], i); bounds[1] = max(bounds[1], i);
    bounds[2] = min(bounds[2], j); bounds[3] = max(bounds[3], j);
} //

bool satisfied(int y, int x) {
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i == y && j == x) continue;
            if (ground[i][j].has_elf) return false;
        }
    }
    return true;
} //

bool sim_round() {
    bool no_motion = true;
    for (int i = bounds[0]; i <= bounds[1]; i++) {
        for (int j = bounds[2]; j <= bounds[3]; j++) {
            if (ground[i][j].has_elf) {
                if (satisfied(i, j)) continue;
                no_motion = false;
                propose_loc(i, j);
            }
        }
    }
    if (no_motion) return true;
    for (int i = bounds[0] - 1; i <= bounds[1] + 1; i++) {
        for (int j = bounds[2] - 1; j <= bounds[3] + 1; j++) { //expand range in case
            if (ground[i][j].proposed && ground[i][j].can_move) {
                define_bounds(i, j); //set bounds
                ground[ground[i][j].prev[0]][ground[i][j].prev[1]] = {0, 0, 0};
                ground[i][j] = {1, 0, 0};
            } else {
                ground[i][j].proposed = 0;
            }
        }
    }
    int ndir[4] = {directions[1], directions[2], directions[3], directions[0]};
    for (int i = 0; i < 4; i++)
        directions[i] = ndir[i];
    return false;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s;
    int n = 0, total_elves = 0;
    while (getline(fin, s)) {
        for (int i = 0; i < s.size(); i++)
            if (s.at(i) == '#') {
                define_bounds(n + OFFSET, i + OFFSET);
                ground[n + OFFSET][i + OFFSET].has_elf = true;
                total_elves++;
            }
        n++;
    } //
    int ans = 1;
    for (int i = 0; i < ROUNDS; i++)
        sim_round();
    if (part_one) {
        ans = (bounds[1] - bounds[0] + 1) * (bounds[3] - bounds[2] + 1) - total_elves;
    } else {
        ans += ROUNDS;
        while (!sim_round()) ans++;
    }
    cout << ans;
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start);
    printf("\n%.4f ms\n", elapsed.count()*1e-6);
    return 0;
}
