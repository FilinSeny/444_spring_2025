﻿#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


struct node {
    long long sum;
    long long push = 0;
    bool is_pushed = true;
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


void relax(node * root) {
    if (root->is_pushed) return;
    root->sum = root->push * (root->r - root->l);
    if ((root->r - root->l) != 1) {
        root->r_son->push = root->push;
        root->r_son->is_pushed = false;
        root->l_son->push = root->push;
        root->l_son->is_pushed = false;
    }
    root->push = 0;
    root->is_pushed = true;
}







long long get_val(node* root, int L, int R) {
    if (!root) return 0;
    relax(root);
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


void upd(node * root, int ind, int new_val) {

    if (!root || root->l >  ind|| root->r <= ind) {
        return;
    }
    relax(root);
    if (root->r - root->l == 1) {
        root->sum = new_val;
        return;
    } else {
        upd(root->l_son, ind, new_val);
        upd(root->r_son, ind, new_val);
        root->sum = root->l_son->sum + root->r_son->sum;
    }
}


void upd_2(vector<int> & tree, int ind, int new_val, int l, int r, int i = 1) {
    if (l > ind || r <= ind) {
        return;
    }
    if (r - l == 1) {
        tree[i] = new_val;
        return;
    }
    int m = (l + r) / 2;
    upd_2(tree, ind, new_val, l, m, i * 2);
    upd_2(tree, ind, new_val, m, r, 1 + i * 2);
    tree[i] = tree[2*i] + tree[2*i + 1];
    return;
}





void group_upd(node * root, int L, int R, int new_val) {
    if (!root) return;
    if (root->l >= L && root->r <= R) {
        relax(root);
        root->push = new_val;
        root->is_pushed = false;
        return;
    } 
    if (root->l >= R || root->r <= L) {
        return;
    }
    relax(root);
    group_upd(root->l_son, L, R, new_val);
    group_upd(root->r_son, L, R, new_val);
    relax(root->l_son);
    relax(root->r_son);
    root->sum = root->l_son->sum + root->r_son->sum;
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
    cout << "done";

    group_upd(root, 1, 3, 90);
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int L, R;
        cin >> L >> R;
        L--;
        cout << get_val(root, L, R) << ' ';
    }
    return 0;
}
