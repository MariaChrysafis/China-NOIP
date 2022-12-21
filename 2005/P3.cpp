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
class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};

vector<int> f1 (vector<set<int> > adj) {
    int t = adj.size();
    vector<bool> marked;
    marked.assign(t, false);
    vector<int> v;
    int cur = 0;
    for (int i = 0; i < t; i++) {
        marked[cur] = true;
        v.push_back(cur);
        for (auto& x: adj[cur]) {
            if (!marked[x]) {
                cur = x;
                break;
            }
        }
    }
    return v;
}

int g (vector<int> v) {
    vector<int> c;
    c.assign(v.size(), 0);
    for (int i = 0; i < v.size(); i++) {
        c[(v[i] - i + v.size()) % v.size()] += 1;
    }
    return (int)v.size() - *max_element(c.begin(), c.end());
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    vector<set<int> > adj(t);
    for (int _ = 0; _ < t; _++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        assert(a != b);
        adj[_].insert(a), adj[_].insert(b);
    }
    for (int i = 0; i < adj.size(); i++) {
        if (adj[i].size() != 2) {
            cout << -1;
            exit(0);
        }
        for (int j: adj[i]) {
            if (adj[i].count(j) != adj[j].count(i)) {
                cout << -1;
                exit(0);
            }
        }
    }
    DisjointSetUnion dsu(adj.size());
    for (int i = 0; i < adj.size(); i++) {
        for (int j: adj[i]) {
            dsu.join(i, j);
        }
    }
    assert(dsu.getConnectedComponents() == 1);
    auto v = f1(adj);
    auto v1 = v;
    reverse(v1.begin(), v1.end());
    cout << min(g(v), g(v1));
}
