#include <iostream>
#include <vector>

using namespace std;

vector<int> T;

int sum (int i)
{
    int res = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        res += T[i];
    }

    return res;
}

void inc (int i, int delta)
{
	for (; i < T.size(); i = (i | (i + 1))) {
        T[i] += delta;
	}
}

int sum (int l, int r)
{
	return sum(r) - sum(l - 1);
}

void init (vector<int> a)
{
	for (int i = 0; i < a.size(); ++i) {
        inc(i, a[i]);
	}
}

int main() {
    int n = 11;
    T.resize(n);
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};


    init(a);

    for (auto el : T) {
            cout << el << ' ';
    }
    cout <<  '\n' << sum(0, 10);
}
