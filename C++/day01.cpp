#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdio.h>
using namespace std;
ifstream fin("i");
bool part_one = false;

int main() {
    long start = time(NULL);
    int cur_cals = 0, elves[100000], i = 0;
    string s;
    while (getline(fin, s)) {
        if (s == "\n\n") {
            elves[i] = cur_cals;
            cur_cals = 0;
            i++;
        } else cur_cals += stoi(s);
    }
    sort(elves, elves + i, [](int &a, int &b) -> bool {return a > b;});
    if (part_one) cout << elves[0];
    else cout << elves[0] + elves[1] + elves[2];
    long end = time(NULL);
    cout << endl << end - start << " ms" << endl;
    return 0;
}
