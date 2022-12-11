#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
int scale = (part_one ? 4 : 13);

int main() {
    long start = time(NULL);
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
    long end = time(NULL);
    cout << endl << end - start << " ms" << endl;
    return 0;
}
