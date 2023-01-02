#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <iomanip>
#include <bitset>
#include <queue>
#include <cmath>
#include <numeric>
#include <functional>
#include <climits>
#include <map>
#include <unordered_map>
#include <stack>
#include <ctime>

using namespace std;
int main () {
    int64_t N, m;
    cin >> N >> m;
    vector<pair<int64_t,pair<int64_t,int64_t>> > tot[m];
    for (int i = 0; i < m; i++) {
        int64_t v, p, q;
        cin >> v >> p >> q;
        if (q > 0) {
            tot[q - 1].push_back({0, {v, p}});
        } else {
            tot[i].push_back({1, {v, p}});
        }
    }
    vector<int64_t> dp(N + 1);
    for (int i = 0; i <= N; i++) {
        dp[i] = 0;
    }
    for (auto& p: tot) {
        if (p.empty()) {
            continue;
        }
        assert(p[0].first == 1);
        assert(p.size() <= 3);
        auto prev_dp = dp;
        for (int i = 1; i < (1 << p.size()); i += 2) {
            int64_t ans = 0;
            int64_t money = 0;
            for (int j = 0; j < p.size(); j ++) {
                if (i & (1 << j)) {
                    ans += p[j].second.first * p[j].second.second;
                    money += p[j].second.first;
                }
            }
            for (int x = N; x >= money; x--) {
                dp[x] = max(dp[x], prev_dp[x - money] + ans);
            }
        }
    }
    cout << dp[N];
}
