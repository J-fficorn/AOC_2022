#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;
ifstream fin("i");
bool part_one = false;
struct item {
    int n, p;
    char c;
} freq[58];

void initiate_freq() {
    for (int i = 0; i < 26; i++) {
        freq[i].n = 0;
        freq[i + 32].n = 0;
        freq[i].c = (char) (65 + i);
        freq[i + 32].c = (char) (97 + i);
        freq[i].p = i + 26 + 1;
        freq[i + 32].p = i + 1;
    }
}

int main() {
    long start = time(NULL);
    string s;
    int sum = 0, lines = 1;
    initiate_freq();
    while (fin >> s) {
        if (part_one) {
            int half = s.size() / 2;
            for (int i = 0; i < half; i++) {
                if (freq[((int) (s.at(i))) - 65].n == 0) freq[((int) (s.at(i))) - 65].n++;
            }
            for (int i = 0; i < half; i++) {
                if (freq[((int) (s.at(i + half))) - 65].n == 1) {
                    sum += freq[((int) (s.at(i + half))) - 65].p;
                    break;
                }
            }
            initiate_freq();
        } else {
            if (lines < 3) {
                for (int i = 0; i < s.size(); i++)
                    if (freq[((int) (s.at(i))) - 65].n == (lines - 1)) freq[((int) (s.at(i))) - 65].n++;
                lines++;
            } else {
                for (int i = 0; i < s.size(); i++) {
                    if (freq[((int) (s.at(i))) - 65].n == 2) {
                        sum += freq[((int) (s.at(i))) - 65].p;
                        break;
                    }
                }
                initiate_freq();
                lines = 1;
            }
        }
    }
    cout << sum;
    long end = time(NULL);
    cout << endl << end - start << " ms" << endl;
    return 0;
}
