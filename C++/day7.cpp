#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
struct file {
    int size, index, parent_index, total_size;
    string name;
    vector<int> children;
};
vector<file> folders;
bool visited[500] = {false};

int dfs_sum(int x) {
    int total_size = folders[x].size;
    visited[x] = true;
    if (folders[x].children.size() != 0) { //isnt file
        for (int i = 0; i < folders[x].children.size(); i++) { //visit dirs + files
            if (!visited[folders[x].children[i]]) {
                total_size += dfs_sum(folders[x].children[i]);
            }
        }
    }
    folders[x].total_size = total_size;
    return total_size;
}

void print_file(int x) {
    cout << folders[x].size << " " << folders[x].index << " " << folders[x].parent_index <<
     " " << folders[x].total_size << " " << folders[x].name << " " << folders[x].children.size()
     << " " << visited[x] << endl;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, cmd[10], parent_name;
    int n = 0, num_files = 1, folder_index = 0, size;
    file main = {0, 0, 0, 0, "/"}; folders.push_back(main);
    int total_directory_size = 0;
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ' ')) {
            cmd[n] = t; n++;
        }
        if (cmd[0] == "$") {
            if (cmd[1] == "cd") {
                if (cmd[2] == "/") {
                    folder_index = 0; //return to /
                } else if (cmd[2] == "..") {
                    folder_index = folders[folder_index].parent_index; //return to parent
                } else {
                    for (int i = 0; i < folders[folder_index].children.size(); i++) { //all children
                        int x = folders[folder_index].children[i];
                        if (folders[x].name == cmd[2])
                            folder_index = folders[x].index; //find searched directory
                    }
                }
            } //cmd
        } else { 
            file dir;
            if (cmd[0] == "dir") dir.size = 0;
            else dir.size = stoi(cmd[0]);
            dir.index = num_files;
            dir.parent_index = folder_index;
            dir.name = cmd[1];
            dir.total_size = 0;
            folders.push_back(dir);
            folders[folder_index].children.push_back(dir.index);
            num_files++;
        } //file/dir
        n = 0;
    }
    for (int i = 0; i < folders.size(); i++) {
        if (!visited[i]) folders[i].total_size = dfs_sum(i);
        // print_file(i);
    } //sum files
    if (part_one) {
        for (int i = 0; i < folders.size(); i++)
            if (folders[i].size == 0 && folders[i].total_size <= 100000)
                total_directory_size += folders[i].total_size;
    } else {
        int min_max = folders[0].total_size, needed = min_max - (70000000 - 30000000);
        // cout << min_max << endl;
        for (int i = 0; i < folders.size(); i++) {
            if (folders[i].size == 0 && folders[i].total_size - needed > 0)
                min_max = min(min_max, folders[i].total_size);
        }
        total_directory_size = min_max;
    } //total hours wasted 
    cout << total_directory_size;
    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << endl << elapsed.count() * 1e-9 << " ns" << endl;
    return 0;
}
