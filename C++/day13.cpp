#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
struct packet {
    bool is_list;
    int value;
    vector<packet> data;
};
vector<packet> all_packets;

int right_order(packet a, packet b) {
    if (!a.is_list && !b.is_list) {
        if (a.value < b.value) return 1;
        if (a.value > b.value) return -1;
    } else if (a.is_list && b.is_list) {
        int a_n = a.data.size(), b_n = b.data.size(), length = min(a_n, b_n);
        for (int i = 0; i < length; i++) {
            int data_comparison = right_order(a.data[i], b.data[i]);
            if (data_comparison) return data_comparison;
        }
        if (a_n < b_n) return 1;
        if (a_n > b_n) return -1;
    } else { //list & int
        if (a.is_list) {
            b.is_list = true; b.data.push_back({false, b.value});
        } else { //b is list, a int
            a.is_list = true; a.data.push_back({false, a.value});
        }
        return right_order(a, b);
    }
    return 0;
}

packet make_packet(ss &s) {
    packet p;
    if (s.peek() == '[') {
        p.is_list = true;
        char c; s >> c;
        bool parse_comma = false;
        while (s.peek() != ']') {
            if (parse_comma) s >> c;
            packet sub_data = make_packet(s);
            p.data.push_back(sub_data);
            parse_comma = true;
        }
        s >> c;
    } else {
        p.is_list = false;
        s >> p.value;
    }
    return p;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t;
    int n = 1, total_index = 0;
    while (getline(fin, s) && getline(fin, t)) {
        ss x(s); ss y(t);
        packet a = make_packet(x), b = make_packet(y);
        if (right_order(a, b) == 1) total_index += n;
        all_packets.push_back(a); all_packets.push_back(b);
        getline(fin, s);
        n++;
    }
    if (!part_one) {
        total_index = 1;
        packet two_limiter = {true, 10, {{false, 2}}}, six_limiter = {true, 10, {{false, 6}}};
        all_packets.push_back(two_limiter); all_packets.push_back(six_limiter);
        sort(all_packets.begin(), all_packets.end(), [](packet a, packet b) -> bool {return right_order(a, b) == 1;});
        for (int i = 0; i < all_packets.size(); i++)
            if (all_packets[i].value == 10) total_index *= (i + 1);
    }
    cout << total_index;
    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << endl << elapsed.count() << " ms" << endl;
    return 0;
}
