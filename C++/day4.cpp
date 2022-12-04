#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
using namespace std;
ifstream fin("i");
bool part_one = false;

int main() {
    long start = time(NULL);
    string s, t, u;
    int contained = 0;
    while (fin >> s) {
        stringstream ss(s);
        int values[4], i = 0;
        while (getline(ss, t, ',')) {
            stringstream st(t);
            while (getline(st, u, '-')) {
                values[i] = stoi(u);
                i++;
            }
        }
        // for (int i = 0; i < 4; i++) cout << values[i] << " ";
        if (part_one) {
            if ((values[0] >= values[2] && values[1] <= values[3]) ||
                (values[2] >= values[0] && values[3] <= values[1])) contained++;
        } else {
            int points[100] = {0}, pre[100 + 1];
            points[values[0]]++; points[values[1] + 1]--;
            points[values[2]]++; points[values[3] + 1]--;
            // for (int i = 0; i < 10; i++) cout << points[i] << " ";
            pre[0] = 0;
            for (int i = 1; i <= 100; i++)
                pre[i] = points[i] + pre[i - 1];
            for (int i = 0; i <= 100; i++) {
                if (pre[i] >= 2) {
                    contained++;
                    break;
                }
            }
        }
    }
    long end = time(NULL);
    cout << contained;
    cout << endl << end - start << " ms" << endl;
    return 0;
}
