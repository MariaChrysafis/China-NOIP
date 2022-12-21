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
#include <climits>
#include <ctime>

using namespace std;

bool reachable(int x, int y, int S, int T) {
    if (S == T) {
        return ((y - x) % T == 0);
    }
    y = y - x;
    if (abs(y) >= 1000) {
        return true;
    }
    bool reachable[y + 1];
    for (int i = 0; i <= y; i++) {
        reachable[i] = false;
    }
    reachable[0] = true;
    for (int i = 0; i <= y; i++) {
        for (int j = S; j <= T; j++) {
            if (i + j <= y && reachable[i]) {
                reachable[i + j] = true;
            }
        }
    }
    return reachable[y];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int L, S, T, M;
    cin >> L >> S >> T >> M;
    set<int> stones;
    set<int> dummy;
    for (int _ = 0; _ < M; _++) {
        int a;
        cin >> a;
        stones.insert(a);
    }
    stones.insert(0);
    stones.insert(L);
    for (int i: stones) {
        for (int x = -T; x <= T; x++) {
            dummy.insert(max(i - x, 0));
        }
    }
    stones.erase(0);
    stones.erase(L);
    vector<int> interesting = std::vector<int>(dummy.begin(), dummy.end());
    int dp[interesting.size()];
    dp[0] = 0;
    int ans = M;
    for (int i = 1; i < interesting.size(); i++) {
        dp[i] = M;
        bool encountered_stone = false;
        for (int j = i - 1; j >= 0; j--) {
            if (encountered_stone && abs(interesting[i] - interesting[j]) > T) {
                break;
            }
            encountered_stone |= stones.count(interesting[j]);
            if (reachable(interesting[j], interesting[i], S, T)) {
                dp[i] = min(dp[i], dp[j] + (int) stones.count(interesting[i]));
            }
        }
        if (interesting[i] >= L) {
            ans = min(ans, dp[i]);
        }
    }
    cout << ans;
    exit(0);
}
