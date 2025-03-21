#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n = 4;
int m = 4;
vector<vector<long long>> tree_2d(4*n, vector<long long> (4*m));



void build_col(vector<vector<long long>> & data, int lx, int rx, int j, int ly = 0, int ry = n, int i = 1) {
    if (ry - ly == 1) {
        if (rx - lx == 1) {
            tree_2d[i][j] = data[ly][lx];
        } else {
            tree_2d[i][j] = tree_2d[i][2*j] + tree_2d[i][2 * j + 1];
        }
        return;
    }
    int my = (ly + ry) / 2;
    build_col(data, lx, rx, j, ly, my, i * 2);
    build_col(data, lx, rx, j, my, ry, i * 2 + 1);
    tree_2d[i][j] = tree_2d[i * 2][j] + tree_2d[i * 2 + 1][j];
}



void buld_colums( vector<vector<long long>> & data, int lx = 0, int rx = m, int j = 1) {
    if (rx - lx > 1) {
        buld_colums(data, lx, (lx + rx) / 2, j *2);
        buld_colums(data, (lx + rx) / 2, rx, j * 2 + 1);
    }

    build_col(data, lx, rx, j, 0, n, 1);
}



long long sum_in_colum(int Lx, int Rx, int Ly, int Ry,
                         int lx, int rx, int j,
                         int ly = 0, int ry = 0, int i = 1)
{
    if (ly >= Ry || ry <= Ly)
    {
        return 0;
    }
    if (ly >= Ly && ry <= Ry) {
        return tree_2d[i][j];
    }
    return sum_in_colum(Lx, Rx, Ly, Ry, lx, rx, j, ly, (ly + ry) / 2, i * 2) +
    sum_in_colum(Lx, Rx, Ly, Ry, lx, rx, j, (ly + ry) / 2, ry, i * 2 + 1);

}



long long sum_of_clolums(int Lx, int Rx, int Ly, int Ry,
                         int lx = 0, int rx = n - 1, int j = 1) {
    if (lx >= Rx || rx <= Lx) {
        return 0;
    }
    if (lx >= Lx && rx <= Rx) {
        return sum_in_colum(Lx, Rx, Ly, Ry, lx, rx, j, 0, n, 1);
    }
    return sum_of_clolums(Lx, Rx, Ly, Ry, lx, (rx + lx) / 2, j * 2) +
    sum_of_clolums(Lx, Rx, Ly, Ry, (lx + rx) / 2, rx, j * 2 + 1);
}


int main()
{
    vector<vector<long long>> data(n, vector<long long> (m));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> data[i][j];
        }
    }


    buld_colums(data, 0, m, 1);


    for (int i = 0; i < tree_2d.size(); ++i) {
        for (int j = 0; j < tree_2d[0].size(); ++j) {
            cout << tree_2d[i][j] << '\t';
        }
        cout << endl;
    }
    return 0;
}
