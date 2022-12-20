#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
#include <queue>
#include <cmath>
#include <map>
#include <stack>
#include <ctime>
using namespace std;
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return max(a,b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
int lis (vector<int> v) {
    int n = v.size();
    Seg<int> st;
    st.init(n + 2);
    vector<int> dp(n);
    set<int> mySet;
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
        mySet.insert(v[i]);
    }
    map<int,int> myMap;
    int cntr = 0;
    for (int i: mySet) {
        myMap[i] = ++cntr;
    }
    for (int i = 0; i < n; i++) {
        v[i] = myMap[v[i]];
    }
    for (int i = 0; i < n; i++) {
        st.upd(v[i], st.query(0, v[i] - 1) + 1);
    }
    return st.query(0, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int myMax = 0;
    int dp[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] < arr[j] && arr[j] > arr[k]) {
                    dp[i][k] = 3;
                }
            }
        }
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n; i++) {
            int j = i + len - 1;
            if (j < 0 || j >= n) {
                continue;
            }
            if (dp[i][j] >= 3) {
                for (int k = 0; k < n; k++) {
                    if (k < i && arr[k] < arr[i]) {
                        dp[k][j] = max(dp[k][j], dp[i][j] + 1);
                    }
                    if (k > j && arr[k] < arr[j]) {
                        dp[i][k] = max(dp[i][k], dp[i][j] + 1);
                    }
                }
            }
        }
    }
    myMax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            myMax = max(myMax, dp[i][j]);
        }
    }
    myMax = max(myMax, lis(arr));
    reverse(arr.begin(), arr.end());
    myMax = max(myMax, lis(arr));
    cout << n - myMax;
}
