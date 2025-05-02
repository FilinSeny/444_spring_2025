struct node {
  int x; //key
  int y; //priority
  node *l_son = nullptr;
  node *r_som + nullptr;

  node(int _x) {
    x = _x;
    y = rand();
  }
}


node *merge(node *r, node *l) {
  if (r == nullptr) {
    return l;
  }
  if (l == nullptr) {
    return r;
  }
  if (r->y > l->y) {
    r->l_son = merge(l, r->l_son);
    return r;
  }
  else {
    l->r_son = merge(l->r_son, r);
    return l;
  }
}


pair<node *, node*> split(node *root, int x) {
  if (root == nullptr) return {nullptr, nullptr};
  if (root->x < x) {
    auto p = split(root->r_son, x);
    root->r_son = p.first;
    return {root, p.second};
  }
  else {
    auto p = split(root->l_son, x);
    root->l_son = p.second;
    return {p.first, parent};
  }
}

bool find(node *root, int x) {
  if (root == nullptr) return false;
  if (root->x == x) return true;
  if (root->x < x)
    return find(root->l_son, x);
  else {
    return find(root->r_son, x);
  }
}


bool find(node *root, int x) {
  auto p1 = split(root, x);
  auto p2 = split(p1.second, x + 1);
  bool res = p2.first;
  p1.second= merge(p2.first, p2.second);
  root = merge(p1.first, p1.second);
  return res;
}

void erase(node *root, int x) {
  auto p1 = split(root, x);
  auto p2 = split(p1.second, x + 1);
  if (p2.first) {
    delete(p2.first);
  }

  root = merge(p1.first, p2.second);

}


void insert(node * root, int x) {
    node * new_node = new(node(x))
    auto p = split(root, x);
    root = merge(p.first, merge(new_node, p.second));
}
