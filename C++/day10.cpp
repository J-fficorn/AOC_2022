#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
int values[1000]; //cycle as index

int sum_interesting_freqs(int cycle_numbers[6], int sum = 0) {
    for (int i = 0; i < 6; i++)
        sum += cycle_numbers[i] * values[cycle_numbers[i]];
    return sum;
}

void render_crt() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            int cycle = 40 * i + j + 1, pos = j;
            if (abs(values[cycle] - pos) < 2) cout << "#";
            else cout << ".";
        }
        cout << endl;
    }
}

int main() {    
    auto time_start = chrono::steady_clock::now();
    string s, t, cmd[2];
    int n = 0, cycle = 1, value = 1;
    values[cycle] = value; //0th cycle = 1
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ' ')) {
            cmd[n] = t; n++;
        }
        n = 0;
        cycle++;
        values[cycle] = value;
        if (cmd[0] == "noop") {
            cycle++;
            values[cycle] = value;
        } else if (cmd[0] == "addx") {
            cycle++;
            value += stoi(cmd[1]);
            values[cycle] = value;
            //sim 2 cycles
        }
    }
    int cycle_numbers[] = {20, 60, 100, 140, 180, 220};
    cout << sum_interesting_freqs(cycle_numbers) << endl;
    render_crt();
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    printf("\n%.2f ms\n", time_elapsed.count());
    return 0;
}
