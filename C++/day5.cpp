#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stack>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
vector<stack<char>> supplies;
vector<vector<char>> input;

int main() {
    long start = time(NULL);
    string s, t, u, top_containers = "";
    int stacks = 0;
    for (int i = 0; i < 20; i++) {
        supplies.push_back(stack<char>());
        input.push_back(vector<char>());
    }
    while (getline(fin, s)) {
        if (s.size() < 2) break;
        int n = 0;
        bool finished = false;
        for (int i = 1; i < s.size(); i += 4) {
            if (s.at(i) != ' ') {
                if (s.at(i) == '1') break;
                input[n].push_back(s.at(i));
                n++;
            } else n++;
        }
        stacks = n;
    }
    for (int i = 0; i < input.size(); i++) {
        for (int j = input[i].size() - 1; j >= 0; j--) {
            supplies[i].push(input[i][j]);
        }
    }
    while (getline(fin, s)) {
        ss x(s);
        string t, inst[10];
        int n = 0;
        while (getline(x, t, ' ')) {
            inst[n] = t;
            n++;
        }
        int num_inst[3] = {stoi(inst[1]), stoi(inst[3]) - 1, stoi(inst[5]) - 1};
        if (part_one) {
            for (int i = 0; i < num_inst[0]; i++) {
                supplies[num_inst[2]].push(supplies[num_inst[1]].top());
                supplies[num_inst[1]].pop();
            }
        } else {
            stack<char> temp;
            for (int i = 0; i < num_inst[0]; i++) {
                temp.push(supplies[num_inst[1]].top());
                supplies[num_inst[1]].pop();
            }
            while (!temp.empty()) {
                supplies[num_inst[2]].push(temp.top());
                temp.pop();
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        cout << supplies[i].top();
    }
    long end = time(NULL);
    cout << endl << end - start << " ms" << endl;
    return 0;
}
