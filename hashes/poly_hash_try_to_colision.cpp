#include <iostream>
#include <set>
#include <cmath>
#include <map>

using namespace std;


long long P = 29;
long long M = 1e9 + 9;


long long get_hash(const string & s) {
    long long res = 0;
    long long deg_p = 1;

    for (int i = 0; i < s.size(); ++i) {
        res += (deg_p * (s[i] - 'a' + 1)) % M;
        deg_p = (deg_p * P) % M;
    }

    return res;
}



int main()
{
    string s;
    cin >> s;
    map<long long, int> n_of_hashes;

    for(int i = 1; i < pow(26, 5); ++i) {
        s = "";
        int k = i;
        while (k >= 0 && s.size() < 5) {
            s += (k % 26) + 'a';
            k /= 26;
        }

        if (s.size() < 5) {
            continue;
        }

        if (i % 100000 == 0) {
            cout << i << endl;
        }

        long long h = get_hash(s);
        if (n_of_hashes.find(h) == n_of_hashes.end()) {
            n_of_hashes[h] = 1;
        } else {
            n_of_hashes[h] += 1;
        }
    }

    for (auto el_p: n_of_hashes) {
        cout << el_p.first << ' ' << el_p.second << endl;
    }


    return 0;
}
