#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <chrono>
using namespace std;
ifstream fin("i");
bool part_one = false;

int main() {
    auto time_start = chrono::steady_clock::now();
    int cur_cals = 0, elves[100000], i = 0;
    string s;
    while (getline(fin, s)) {
        if (s.size() <= 1) {
            elves[i] = cur_cals;
            cur_cals = 0;
            i++;
        } else cur_cals += stoi(s);
    }
    sort(elves, elves + i, [](int &a, int &b) -> bool {return a > b;});
    if (part_one) cout << elves[0];
    else cout << elves[0] + elves[1] + elves[2];
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    cout << endl << time_elapsed.count() << " ms" << endl;
    return 0;
}
