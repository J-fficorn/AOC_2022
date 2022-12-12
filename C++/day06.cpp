#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
int scale = (part_one ? 4 : 13);

int main() {
    auto time_start = chrono::steady_clock::now();
    string s;
    getline(fin, s);
    for (int i = scale; i < s.size(); i++) {
        bool valid = true;
        for (int j = i - scale; j <= i; j++) {
            for (int k = i - scale; k <= i; k++) {
                if (j == k) continue;
                if (s.at(j) == s.at(k)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        if (valid) {
            cout << i + 1;
            break;
        }
    }
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    cout << endl << time_elapsed.count() << " ms" << endl;
    return 0;
}
