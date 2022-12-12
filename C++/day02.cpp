#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <chrono>
using namespace std;
ifstream fin("i");
bool part_one = false;
struct Move {
    char c, win, loss;
    int pts;
} moves[26];

int main() {
    auto time_start = chrono::steady_clock::now();
    int total_score = 0;
    moves[0] = {'A', 'Z', 'Y', 1};
    moves[1] = {'B', 'X', 'Z', 2};
    moves[2] = {'C', 'Y', 'X', 3};
    moves[23] = {'X', 'C', 'B', 1};
    moves[24] = {'Y', 'A', 'C', 2};
    moves[25] = {'Z', 'B', 'A', 3};
    string s;
    while (getline(fin, s)) {
        Move elf_move = moves[((int) s.at(0)) - 65], your_move = moves[((int) s.at(2)) - 65];
        if (part_one) {
            if (elf_move.win == your_move.c) total_score += your_move.pts;
            else if (your_move.win == elf_move.c) total_score += your_move.pts + 6;
            else total_score += your_move.pts + 3;
        } else {
            if (your_move.c == 'X') total_score += moves[((int) elf_move.win) - 65].pts;
            else if (your_move.c == 'Z') total_score += moves[((int) elf_move.loss) - 65].pts + 6;
            else total_score += 6 - moves[((int) elf_move.loss) - 65].pts - moves[((int) elf_move.win) - 65].pts + 3;
        }
    }
    cout << total_score;
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    cout << endl << time_elapsed.count() << " ms" << endl;
    return 0;
}
