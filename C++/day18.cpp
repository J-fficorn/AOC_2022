#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>
#define ss stringstream
using namespace std;
ifstream fin("i");
bool part_one = false;
int scan[25][25][25] = {0}, visited[25][25][25] = {0};
int dx[6] = {-1, 1, 0, 0, 0, 0}, dy[6] = {0, 0, -1, 1, 0, 0}, dz[6] = {0, 0, 0, 0, -1, 1};

constexpr inline bool in_bounds(int a) { return a >= 0 && a < 25; }

int flood_fill(int x, int y, int z, int surface_area = 0) {
    visited[x][y][z] = 1;
    for (int i = 0; i < 6; i++) {
        int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
        if (in_bounds(nx) && in_bounds(ny) && in_bounds(nz)) {
            if (scan[nx][ny][nz] && !visited[nx][ny][nz])
                surface_area = flood_fill(nx, ny, nz, surface_area);
            if (!scan[nx][ny][nz])
                surface_area++;
        }
    }
    return surface_area;
}

int flood_air(int x, int y, int z, int surface_area = 0) {
    visited[x][y][z] = 2;
    for (int i = 0; i < 6; i++) {
        int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
        if (in_bounds(nx) && in_bounds(ny) && in_bounds(nz)) {
            if (!visited[nx][ny][nz]) //is air & not ff'd & not lava 
                surface_area += flood_air(nx, ny, nz);
            if (scan[nx][ny][nz])
                surface_area++;
        }
    }
    return surface_area;
}

int main() {
    auto start = chrono::steady_clock::now();
    string s, t;
    int n = 0, input_n = 0, coords[3];
    while (getline(fin, s)) {
        ss x(s);
        while (getline(x, t, ','))
            coords[input_n++] = stoi(t);
        scan[++coords[0]][++coords[1]][++coords[2]] = 1;
        input_n = 0;
    }
    int surface_area = 0;
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            for (int k = 0; k < 25; k++)
                if (scan[i][j][k] && !visited[i][j][k])
                    surface_area += flood_fill(i, j, k);
    if (!part_one)
        surface_area = flood_air(0, 0, 0);
    cout << surface_area;
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start);
    printf("\n%.4f ms\n", elapsed.count()*1e-6);
    return 0;
}
