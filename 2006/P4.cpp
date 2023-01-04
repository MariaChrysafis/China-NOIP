#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <iomanip>
#include <bitset>
#include <queue>
#include <cstdio>
#include <cmath>
#include <numeric>
#include <ctime>
#include <functional>
#include <climits>
#include <string>
#include <cstring>
#include <limits>
#include <map>
#include <unordered_map>
#include <stack>
#include <ctime>

using namespace std;
const int DIG = 9, BASE = 1000000000, BRUTE = 200;
const unsigned long long BOUND = numeric_limits<unsigned long long>::max () - (unsigned long long) BASE * BASE;

struct bignum
{
    vector<int> digits;

    void trim()
    {
        while ((int) digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
    }

    void add(int pos, int num)
    {
        if (pos >= (int) digits.size())
            digits.resize(pos + 1);

        digits[pos] += num;
    }

    void init(long long x)
    {
        do
        {
            add(digits.size(), x % BASE);
            x /= BASE;
        }
        while (x > 0);
    }

    long long value()
    {
        trim();
        long long x = 0;

        for (int i = (int) digits.size() - 1; i >= 0; i--)
            x = BASE * x + digits[i];

        return x;
    }

    bignum(long long x)
    {
        init(x);
    }

    bignum(int x = 0)
    {
        init(x);
    }

    bignum(char *s)
    {
        int len = strlen(s), first = (len + DIG - 1) % DIG + 1, D = (len + DIG - 1) / DIG;
        digits.resize(D);

        for (int i = 0; i < first; i++)
            digits[D - 1] = digits[D - 1] * 10 + s[i] - '0';

        for (int i = first, d = D - 2; i < len; i += DIG, d--)
            for (int j = i; j < i + DIG; j++)
                digits[d] = digits[d] * 10 + s[j] - '0';

        trim();
    }

    char *str()
    {
        trim();
        char *buf = new char[DIG * digits.size() + 1];
        int pos = 0, d = digits.back();

        do
        {
            buf[pos++] = d % 10 + '0';
            d /= 10;
        }
        while (d > 0);

        reverse(buf, buf + pos);

        for (int i = (int) digits.size() - 2; i >= 0; i--, pos += DIG)
            for (int j = DIG - 1, t = digits[i]; j >= 0; j--)
            {
                buf[pos + j] = t % 10 + '0';
                t /= 10;
            }

        buf[pos] = '\0';
        return buf;
    }

    bool operator < (const bignum &o) const
    {
        if (digits.size() != o.digits.size())
            return digits.size() < o.digits.size();

        for (int i = (int) digits.size() - 1; i >= 0; i--)
            if (digits[i] != o.digits[i])
                return digits[i] < o.digits[i];

        return false;
    }

    bool operator == (const bignum &o) const
    {
        if (digits.size () != o.digits.size())
            return false;

        for (int i = 0; i < (int) digits.size(); i++)
            if (digits[i] != o.digits[i])
                return false;

        return true;
    }

    bignum operator << (int p) const
    {
        bignum temp;
        temp.digits.resize (digits.size() + p);

        for (int i = 0; i < (int) digits.size(); i++)
            temp.digits[i + p] = digits[i];

        for (int i = 0; i < p; i++)
            temp.digits[i] = 0;

        return temp;
    }

    bignum operator >> (int p) const
    {
        bignum temp;
        temp.digits.resize (digits.size() - p);

        for (int i = 0; i < (int) digits.size() - p; i++)
            temp.digits[i] = digits[i + p];

        return temp;
    }

    bignum range(int a, int b) const
    {
        bignum temp = 0;
        temp.digits.resize(b - a);

        for (int i = 0; i < b - a; i++)
            temp.digits[i] = digits[i + a];

        return temp;
    }

    bignum operator + (const bignum &o) const
    {
        bignum sum = o;

        for (int i = 0, carry = 0; i < (int) digits.size() || carry > 0; i++)
        {
            sum.add(i, (i < (int) digits.size() ? digits[i] : 0) + carry);

            if (sum.digits[i] >= BASE)
            {
                sum.digits[i] -= BASE;
                carry = 1;
            }
            else
                carry = 0;
        }

        sum.trim();
        return sum;
    }

    bignum operator - (const bignum &o) const
    {
        bignum diff = *this;

        for (int i = 0, carry = 0; i < (int) o.digits.size() || carry > 0; i++)
        {
            diff.digits[i] -= (i < (int) o.digits.size() ? o.digits[i] : 0) + carry;

            if (diff.digits[i] < 0)
            {
                diff.digits[i] += BASE;
                carry = 1;
            }
            else
                carry = 0;
        }

        diff.trim();
        return diff;
    }

    bignum operator * (const bignum &o) const
    {
        const bignum *a = this, *b = &o;

        if (a->digits.size() > b->digits.size())
            swap(a, b);

        if ((int) a->digits.size() <= BRUTE)
        {
            bignum prod = 0;
            prod.digits.resize(digits.size() + o.digits.size() - 1);
            unsigned long long sum = 0, carry = 0;

            for (int i = 0; i < (int) digits.size() + (int) o.digits.size() - 1 || carry > 0; i++)
            {
                sum = carry % BASE;
                carry /= BASE;

                for (int j = max(i - (int) o.digits.size() + 1, 0); j <= min((int) digits.size() - 1, i); j++)
                {
                    sum += (unsigned long long) digits[j] * o.digits[i - j];

                    if (sum >= BOUND)
                    {
                        carry += sum / BASE;
                        sum %= BASE;
                    }
                }

                carry += sum / BASE;
                prod.add(i, sum % BASE);
            }

            prod.trim();
            return prod;
        }

        int mid = a->digits.size() / 2;
        bignum a1 = a->range(0, mid), a2 = a->range(mid, a->digits.size()), b1 = b->range(0, mid), b2 = b->range(mid, b->digits.size());
        bignum x = a2 * b2, z = a1 * b1, y = (a1 + a2) * (b1 + b2) - x - z;
        return (x << 2 * mid) + (y << mid) + z;
    }

    bignum operator * (int mult) const
    {
        bignum prod = 0;
        prod.digits.clear();
        prod.digits.reserve(digits.size() + 1);
        unsigned long long carry = 0;

        for (int i = 0; i < (int) digits.size() || carry > 0; i++) {
            unsigned long long digit = (unsigned long long) (i < (int) digits.size() ? digits[i] : 0) * mult + carry;
            prod.digits.push_back(digit % BASE);
            carry = digit / BASE;
        }

        prod.trim();
        return prod;
    }

    double double_div(const bignum &o) const
    {
        double val = 0, oval = 0;
        int num = 0, onum = 0;

        for (int i = (int) digits.size() - 1; i >= max((int) digits.size() - 3, 0); i--, num++)
            val = val * BASE + digits[i];

        for (int i = (int) o.digits.size() - 1; i >= max((int) o.digits.size() - 3, 0); i--, onum++)
            oval = oval * BASE + o.digits[i];

        return val / oval * ((int) digits.size() - num > (int) o.digits.size() - onum ? BASE : 1);
    }

    pair<bignum, bignum> divmod(const bignum &o) const
    {
        bignum quot = 0, rem = *this, temp;

        for (int i = (int) digits.size() - (int) o.digits.size(); i >= 0; i--) {
            temp = rem.range(i, rem.digits.size());
            int div = (int) temp.double_div(o);
            bignum mult = o * div;

            while (div > 0 && temp < mult) {
                mult = mult - o;
                div--;
            }

            while (div + 1 < BASE && !(temp < mult + o)) {
                mult = mult + o;
                div++;
            }
            rem = rem - (o * div << i);
            if (div > 0) quot.add(i, div);
        }

        quot.trim();
        rem.trim();
        return make_pair(quot, rem);
    }

    bignum operator / (const bignum &o) const
    {
        return divmod(o).first;
    }

    bignum operator % (const bignum &o) const
    {
        return divmod(o).second;
    }

    bignum power(int exp) const
    {
        bignum p = 1, temp = *this;
        while (exp > 0)
        {
            if (exp & 1) p = p * temp;
            if (exp > 1) temp = temp * temp;
            exp >>= 1;
        }
        return p;
    }
};
vector<bool> isPrime;
vector<int> primes;
map<int,int> oc (int n) {
    map<int,int> myMap;
    for (int i: primes) {
        if (i > n) {
            break;
        }
        int k = i;
        while (k <= n) {
            myMap[i] += n/k;
            k *= i;
        }
    }
    return myMap;
}
bignum combo (int n, int k) {
    if (k > n) {
        return 0;
    }
    map<int,int> myMap = oc(n);
    for (auto& p: oc(n - k)) {
        myMap[p.first] -= p.second;
    }
    for (auto& p: oc(k)) {
        myMap[p.first] -= p.second;
    }
    bignum ans = bignum("1");
    for (auto& p: myMap) {
        while (p.second != 0) {
            bignum gamma;
            gamma = p.first;
            ans = ans * gamma;
            p.second--;
        }
    }
    return ans;
}
int main () {
    isPrime.assign(2500, true);
    for (int i = 2; i < isPrime.size(); i++) {
        for (int j = 2 * i; j < isPrime.size(); j += i) {
            isPrime[j] = false;
        }
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    int k, w;
    cin >> k >> w;
    w = min(w, 4608);
    bignum ans;
    ans = 0;
    for (int digits = k + 1; digits <= w; digits++) {
        int x = (digits + k - 1) % k + 1;
        int base = (digits + k - 1)/k - 1;
        int l = (1 << k) - min((1 << x) - 1, (1 << k) - 1 - base) - 1; //up to 512
        int r = (1 << k) - (1 << (x - 1)) - 1;
        if (r + 1 < base + 1 && l < base + 1) {
            continue;
        }
        ans = ans + combo(r + 1, base + 1) - combo(l, base + 1);
    }
    cout << ans.str();
}
