#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n = 4;
int inf = 1e9+7;
int m = 4;
vector<vector<long long>> tree_2d(4*n, vector<long long> (4*m));



void build_y_1dtree(const vector<vector<long long>> & data, const int & lx,const int  & rx, const int & j,
                                                        int ly, int ry, int i = 1) {
    
    if (ry - ly == 1) {
        if (rx - lx == 1) {
            tree_2d[i][j] = data[ly][lx]; ///в случае 0-го слоя в обоях деревьях
        } else {
            ///в случае 0-го слоя в y-дереве
            tree_2d[i][j] = max(tree_2d[i][j * 2], tree_2d[i][j * 2 + 1]);
            ///ходим в деревья меньшей полщины по x (предыдущий слой внешенго дерева) но той же толщины по y
        }
    } else {
        int my = (ly + ry) / 2;
        build_y_1dtree(data, lx, rx, j, ly, my, i * 2);
        build_y_1dtree(data, lx, rx, j, my, ry, i * 2 + 1);
        tree_2d[i][j] = max(tree_2d[i * 2][j], tree_2d[i * 2 + 1][j]);
    }
}



void build_x_2dtree(const vector<vector<long long>> & data, int lx, int rx, int j = 1) { ///строим дерево отрезкоко во х-координате элементами ДО являются ДО по столбцам различной толщины(толщина 2^номер слоя)
    if (rx - lx > 1) {
        build_x_2dtree(data, lx, (lx + rx) / 2, j * 2);
        build_x_2dtree(data, (lx + rx) / 2, rx, j * 2 + 1);
    }
    build_y_1dtree(data, lx, rx, j, 0, n, 1); //строим верщину - одномерное дерево "толщины rx-lx"
}


long long max_y_1d_tree(int Lx, int Rx, int Ly, int Ry, 
                        int lx, int rx, int j,
                        int ly, int ry, int i = 1) {
    if (ly >= Ry || ry <= Ly) {
        return -INF;
    }
    if (ly >= Ly && ry <= Ry) {
        return tree_2d[i][j];
    }
    return max_y_1d_tree(Lx, Rx, Ly, Ry, lx, rx, j, ly, (ly + ry) / 2, i * 2) +
    max_y_1d_tree(Lx, Rx, Ly, Ry, lx, rx, j, (ly + ry) / 2, ry, i * 2 + 1);
}


long long max_x_2d_tree(int Lx, int Rx, int Ly, int Ry, int lx, int rx, int j = 1) {
    if (lx >= Rx || rx <= Lx) {
        return -INF;
    }
    if (lx >= Lx && rx <= Rx) {
        return max_y_1d_tree(Lx, Rx, Ly, Ry, lx, rx, j, 0, n, 1);
    }
    return max_x_2d_tree(Lx, Rx, Ly, Ry, lx, (rx + lx) / 2, j * 2) +
    max_x_2d_tree(Lx, Rx, Ly, Ry, (lx + rx) / 2, rx, j * 2 + 1);
}



int main()
{
    vector<vector<long long>> data(n, vector<long long> (m));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> data[i][j];
        }
    }


    build_x_2dtree(data, 0, m, 1);


    for (int i = 0; i < tree_2d.size(); ++i) {
        for (int j = 0; j < tree_2d[0].size(); ++j) {
            cout << tree_2d[i][j] << '\t';
        }
        cout << endl;
    }
    return 0;
}