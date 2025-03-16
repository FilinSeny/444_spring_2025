#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


struct node {
    long long sum;
    int l, r;
    node* l_son = nullptr, * r_son = nullptr;
};


node* build(const vector<int>& v, int cur_l, int cur_r) {
    node* new_node = new node;
    new_node->l = cur_l;
    (*new_node).r = cur_r;
    if (cur_r - cur_l == 1) {
        new_node->sum = v[cur_l];
        return new_node;
    }

    new_node->l_son = build(v, cur_l, (cur_l + cur_r) / 2);
    new_node->r_son = build(v, (cur_l + cur_r) / 2, cur_r);

    new_node->sum = new_node->l_son->sum + new_node->r_son->sum;
    return new_node;
}

void build_2(const vector<int>& data, int l, int r, vector<int>& tree, int id) {
    if (r - l == 1) {
        tree[id] = data[l];
        return;
    }
    else {
        int m = (l + r) / 2;
        build_2(data, l, m, tree, 2 * id);
        build_2(data, m, r, tree, 2 * id + 1);
        tree[id] = tree[id * 2] + tree[id * 2 + 1];
    }

}







long long get_val(node* root, int L, int R) {
    if (!root) return 0;
    if (root->l >= L && root->r <= R) {
        return root->sum;
    }
    else if (root->l >= R || root->r <= L) {
        return 0;
    }


    return get_val(root->l_son, L, R) + get_val(root->r_son, L, R);
}

int get_val_2(const vector<int>& data, int l, int r, int L, int R, vector<int>& tree, int id) {
    if (l > L && r <= R) {
        return tree[id];
    }
    else if (l >= R || r <= L) {
        return 0;
    }
    return get_val_2(data, l, (l + r) / 2, L, R, tree, id * 2) +
        get_val_2(data, (l + r) / 2, r, L, R, tree, id * 2 + 1);

}




int main()
{
    /// ifstream in("input.in");
     ///ostream out("output.out");
    node a;
    unsigned int n;
    cin >> n;
    unsigned int size = 1;
    while (size < n) {
        size <<= 1;
    }
    size <<= 1;
    size++;
    vector <int> v(n);
    vector<int> tree(size + 1);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    node* root = build(v, 0, n);
    build_2(v, 0, n, tree, 1);

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int L, R;
        cin >> L >> R;
        L--;
        cout << get_val(root, L, R) << ' ';
    }
    ///cout << "done";
    return 0;
}
