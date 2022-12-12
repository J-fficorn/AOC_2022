#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
struct monkey {
    int test, throw_true, throw_false;
    long inspected = 0;
    string op;
    queue<long> items;
} notes[10];
string input[100];

long operate(long old, string op) {
    string function = op.substr(10, 1), s_val = op.substr(12);
    int val = (s_val.at(0) == 'o') ? old : stoi(s_val);
    if (function == "*") return old * val;
    return old + val;
} //operate

queue<long> items(string s, string t = "") {
    ss x(s.substr(18));
    queue<long> temp_item_list;
    while (getline(x, t, ' '))
        temp_item_list.push(stoi(t.substr(0, t.size() - 1)));
    return temp_item_list;
} //create q of items

int main() {
    auto time_start = chrono::steady_clock::now();
    string s;
    int n = 0;
    while (getline(fin, s)) { input[n] = s; n++; }
    int monkey_index = 0, total_modulus = 1;
    for (int i = 0; i < (n + 1) / 7; i++) {
        int indexes[6];
        for (int j = 0; j < 6; j++) indexes[j] = i * 7 + j;
        notes[monkey_index].items = items(input[indexes[1]]);
        notes[monkey_index].op = input[indexes[2]].substr(13);
        notes[monkey_index].test = stoi(input[indexes[3]].substr(21));
            total_modulus *= notes[monkey_index].test;
        notes[monkey_index].throw_true = stoi(input[indexes[4]].substr(29));
        notes[monkey_index].throw_false = stoi(input[indexes[5]].substr(30));
        monkey_index++;
    } //parsing monkey list
    for (int i = 0; i < part_one ? 20 : 10000; i++) { //rounds
        for (int j = 0; j < monkey_index; j++) { //turns
            while (!notes[j].items.empty()) {
                long item = notes[j].items.front(),
                    new_item = operate(item, notes[j].op),
                    relieved = part_one ? new_item / 3 : (new_item % total_modulus);
                if (relieved % notes[j].test == 0)
                    notes[notes[j].throw_true].items.push(relieved);
                else
                    notes[notes[j].throw_false].items.push(relieved);
                notes[j].items.pop();
                notes[j].inspected++;
                // inspect, relief, test, & throw
            }
        }
    }
    sort(notes, notes + monkey_index, [](monkey a, monkey b) -> bool {return a.inspected > b.inspected;});
    auto end = chrono::steady_clock::now();
    cout << notes[0].inspected * notes[1].inspected;
    auto time_end = chrono::steady_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    printf("\n%.2f ms\n", time_elapsed.count());
    return 0;
}
