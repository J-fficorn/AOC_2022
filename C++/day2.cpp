#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdio.h>
using namespace std;
ifstream fin("i");
bool part_one = false;
struct Move {
    char c, win, loss;
    int pts;
} moves[26];

int main() {
    long start = time(NULL);
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
    long end = time(NULL);
    cout << endl << end - start << " ms" << endl;
    return 0;
}
