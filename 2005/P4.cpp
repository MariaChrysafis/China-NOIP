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

//used geeksforgeeks arithmetic stuff

using namespace std;

// Function to find precedence of
// operators.
int64_t precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^') {
        return 3;
    }
    return 0;
}

const int64_t MOD = 1e9 + 7;

// Function to perform arithmetic operations.
int64_t binPow(int64_t x, int64_t y) {
    int64_t res = x, ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}

int64_t mult(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t inv(int64_t a) {
    return binPow(a, MOD - 2);
}

int64_t operation(int64_t a, int64_t b, char op) {
    switch (op) {
        case '+':
            return (a + b) % MOD;
        case '-':
            return (a - b + MOD) % MOD;
        case '*':
            return mult(a, b);
        case '/':
            return mult(a, inv(b));
        case '^':
            return binPow(a, b);
    }
}
int64_t evaluate(string tokens) {
    int64_t i;
    stack<int64_t> values;
    stack<char> ops;
    for (i = 0; i < tokens.length(); i++) {
        if (tokens[i] == ' ') {
        } else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        } else if (isdigit(tokens[i])) {
            int64_t val = 0;
            while (i < tokens.length() &&
                   isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                val %= MOD;
                i++;
            }
            values.push(val);
            i--;
        } else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int64_t val2 = values.top();
                values.pop();
                int64_t val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(operation(val1, val2, op));
            }
            if (!ops.empty()) {
                ops.pop();
            }
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int64_t val2 = values.top();
                values.pop();
                int64_t val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(operation(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }
    while (!ops.empty()) {
        int64_t val2 = values.top();
        values.pop();
        int64_t val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(operation(val1, val2, op));
    }
    return values.top();
}

string replace(string s, char c, string d) {
    string str = "";
    for (int64_t i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            for (char e: d) {
                str.push_back(e);
            }
        } else {
            str.push_back(s[i]);
        }
    }
    return str;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    getline(cin, s);
    string ni;
    getline(cin, ni);
    int64_t n = stoi(ni);
    char c = 'A';
    string ans = "";
    for (int64_t i = 0; i < n; i++) {
        string s1;
        getline(cin, s1);
        //cout << s1 << '\n';
        bool fine = true;
        for (int d = 1; d <= 20; d++) {
            if (evaluate(replace(s1, 'a', to_string(d))) != evaluate(replace(s, 'a', to_string(d)))) {
                fine = false;
            }
        }
        if (fine) {
            ans += c;
        }
        c += 1;
    }
    cout << ans;
}
