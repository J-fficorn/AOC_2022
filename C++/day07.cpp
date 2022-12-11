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
    for (int i = 0; i < folders[x].children.size(); i++) //visit dirs + files
        if (!visited[folders[x].children[i]])
            total_size += dfs_sum(folders[x].children[i]);
    folders[x].total_size = total_size;
    return total_size;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t, cmd[10];
    int n = 0, num_files = 1, folder_index = 0, total_directory_size = 0;
    file main = {0, 0, 0, 0, "/"}; folders.push_back(main);
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ' ')) cmd[n++] = t;
        if (cmd[0] == "$" && cmd[1] == "cd") {
            file x = folders[folder_index];
            switch (cmd[2].at(0)) {
                case '/':
                    folder_index = 0; //return to /
                    break;
                case '.':
                    folder_index = x.parent_index; //return to parent
                    break;
                default:
                    for (int i = 0; i < x.children.size(); i++) //all children
                        if (folders[x.children[i]].name == cmd[2])
                            folder_index = x.children[i]; //find searched directory
                    break;
            } //cmd
        } else if (cmd[0] != "$") { 
            file dir = {
                (cmd[0] == "dir") ? 0 : stoi(cmd[0]), //size
                num_files, folder_index, 0, //index, parent_index, total_size
                cmd[1] //name
            };
            folders.push_back(dir);
            folders[folder_index].children.push_back(dir.index);
            num_files++;
        } //file/dir
        n = 0;
    }
    for (int i = 0; i < folders.size(); i++)
        if (!visited[i]) folders[i].total_size = dfs_sum(i); //sum files
    if (part_one) {
        for (int i = 0; i < folders.size(); i++)
            if (folders[i].size == 0 && folders[i].total_size <= 100000)
                total_directory_size += folders[i].total_size;
    } else {
        int min_max = folders[0].total_size, needed = min_max - (70000000 - 30000000);
        for (int i = 0; i < folders.size(); i++) {
            if (folders[i].size == 0 && folders[i].total_size > needed)
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
