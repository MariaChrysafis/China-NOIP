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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    priority_queue<int64_t> pq;
    for (int i = 0; i < n; i++) {
        int64_t a;
        cin >> a;
        pq.push(-a);
    }
    int64_t ans = 0;
    while (pq.size() != 1) {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        pq.push(x + y);
        ans += x + y;
    }
    cout << -ans;
}
