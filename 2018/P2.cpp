#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <queue>
#include <map>
#include <bitset>

using namespace std;
bitset<25000> rec(vector<int> a) {
    bitset<25000> bs;
    bs.set(0);
    for (int i: a) {
        for (int j = 0; j < 25000; j += i) {
            bs |= (bs << i);
        }
    }
    return bs;
}
void solve () {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<int> b;
    auto bs = rec(a);
    auto cur = rec(b);
    for (int i = 0; i < n; i++) {
        if (!cur[a[i]]) {
            b.push_back(a[i]);
            cur = rec(b);
        }
    }
    cout << b.size() << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
