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
    int t = 12;
    int money = 0;
    int tot = 0;
    for (int _ = 1; _ <= t; _++) {
        int budget;
        cin >> budget;
        money += 300;
        int post_budget = money - budget;
        tot += post_budget/100 * 100;
        post_budget %= 100;
        money = post_budget;
        if (money < 0) {
            cout << -_;
            exit(0);
        }
    }
    cout << tot * 12/10 + money;
}
