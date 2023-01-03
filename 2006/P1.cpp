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
const int MX = 100;
pair<int,int> vec[MX];
vector<int> arr;
int dp[MX][MX];
int res (int i, int j) {
    if (dp[i][j] != 0) {
        return dp[i][j];
    }
    if (i == j) {
        return dp[i][j] = 0;
    }
    if (i + 1 == j) {
        return (dp[i][j] = vec[i].first * vec[j].second * vec[i].second);
    }
    if (i + 2 == j) {
        int a = vec[i].first, b = vec[i].second, c = vec[i + 1].second, d = vec[i + 2].second;
        return (dp[i][j] = max(a * c * d + a * b * c, a * b * d + b * c * d));
    }
    for (int m = i + 1; m <= j; m++) {
        dp[i][j] = max(dp[i][j], res(i, m - 1) + res(m, j) + vec[i].first * vec[j].second * vec[m].first);
    }
    return dp[i][j];
}
int main () {
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int myMax = 0;
    for (int x = 0; x < n; x++) {
        rotate(arr.begin(), arr.begin() + 1, arr.end());
        for (int i = 0; i < MX; i++) {
            for (int j = 0; j < MX; j++) {
                dp[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            vec[i] = make_pair(arr[i], arr[(i + 1) % n]);
        }
        myMax = max(myMax, res(0, n - 1));
    }
    cout << myMax;
}
