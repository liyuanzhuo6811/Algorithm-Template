// {"name": "高精度计算", "intro": "对大整数进行计算。"}
#include <bits/stdc++.h>
using namespace std;
class Big {
  private:
#define CLR(a) memset(a, 0, sizeof(a))
    int MAXN = 9999;     // MAXN 表示每一位最大多少
    int MAXSIZE = 10024; // MAXSIZE 表示最多多少位
    int DLEN = 4;        // DLEN 表示每一位压了多少位
    int a[10024], len;
    bool flag; // flg = true 表示是负数

  public:
    Big() {
        len = 1, flag = false;
        memset(a, 0, sizeof a);
    }
    Big(const int b) {
        int c, d = b;
        len = 0, CLR(a);
        while (d > MAXN) {
            c = d - (d / (MAXN + 1) * (MAXN + 1));
            d = d / (MAXN + 1);
            a[len++] = c;
        }
        a[len++] = d;
    }
    Big(const char *s) {
        int t, k, index, l;
        CLR(a);
        l = strlen(s);
        len = l / DLEN;
        if (l % DLEN) ++len;
        index = 0;
        for (int i = l - 1; i >= 0; i -= DLEN) {
            t = 0, k = i - DLEN + 1;
            if (k < 0) k = 0;
            for (int j = k; j <= i; ++j) t = t * 10 + s[j] - '0';
            a[index++] = t;
        }
    }
    Big(const Big &T) {
        CLR(a);
        for (int i = 0; i < len; ++i) a[i] = T.a[i];
    }
    Big &operator=(const Big &T) {
        CLR(a), len = T.len;
        for (int i = 0; i < len; ++i) a[i] = T.a[i];
        return *this;
    }
    Big operator+(const Big &T) const {
        Big t(*this);
        int big = len;
        if (T.len > len) big = T.len;
        for (int i = 0; i < big; ++i) {
            t.a[i] += T.a[i];
            if (t.a[i] > MAXN) ++t.a[i + 1], t.a[i] -= MAXN + 1;
        }
        if (t.a[big]) t.len = big + 1;
        else t.len = big;
        return t;
    }
    Big operator-(const Big &T) const {
        int big;
        bool ctf;
        Big t1, t2;
        if (*this < T) t1 = T, t2 = *this, ctf = true;
        else t1 = *this, t2 = T, ctf = false;
        big = t1.len;
        int j = 0;
        for (int i = 0; i < big; ++i) {
            if (t1.a[i] < t2.a[i]) {
                j = i + 1;
                while (t1.a[j] == 0) ++j;
                --t1.a[j--];
                while (j > i) t1.a[j--] += MAXN;
                t1.a[i] += MAXN + 1 - t2.a[i];
            } else t1.a[i] -= t2.a[i];
        }
        t1.len = big;
        while (t1.len > 1 && t1.a[t1.len - 1] == 0) --t1.len, --big;
        if (ctf) t1.a[big - 1] = -t1.a[big - 1];
        return t1;
    }
    Big operator*(const Big &T) const {
        Big res;
        int up;
        int te, tee;
        for (int i = 0; i < len; ++i) {
            up = 0;
            for (int j = 0; j < T.len; ++j) {
                te = a[i] * T.a[j] + res.a[i + j] + up;
                if (te > MAXN) tee = te - te / (MAXN + 1) * (MAXN + 1), up = te / (MAXN + 1), res.a[i + j] = tee;
                else up = 0, res.a[i + j] = te;
            }
            if (up) res.a[i + T.len] = up;
        }
        res.len = len + T.len;
        while (res.len > 1 && res.a[res.len - 1] == 0) --res.len;
        return res;
    }
    Big operator/(const int &b) const {
        Big res;
        int down = 0;
        for (int i = len - 1; i >= 0; --i)
            res.a[i] = (a[i] + down * (MAXN + 1)) / b, down = a[i] + down * (MAXN + 1) - res.a[i] * b;
        res.len = len;
        while (res.len > 1 && res.a[res.len - 1] == 0) --res.len;
        return res;
    }
    Big operator^(const int &n) const {
        Big t(n), res(1);
        int y = n;
        while (y) {
            if (y & 1) res = res * t;
            t = t * t, y >>= 1;
        }
        return res;
    }
    int operator%(const int &b) const {
        int d = 0;
        for (int i = len - 1; i >= 0; --i) d = (d * (MAXN + 1) % b + a[i]) % b;
        return d;
    }
    bool operator<(const Big &T) const {
        int ln;
        if (len < T.len) return true;
        if (len == T.len) {
            ln = len - 1;
            while (ln >= 0 && a[ln] == T.a[ln]) --ln;
            if (ln >= 0 && a[ln] < T.a[ln]) return true;
            return false;
        }
        return false;
    }
    bool operator<(const int &t) const {
        Big tee(t);
        return *this < tee;
    }
    void print() const {
        printf("%d", a[len - 1]);
        for (int i = len - 2; i >= 0; --i) { printf("%04d", a[i]); }
    }
    // TODO: Big / Big; Big 位运算; Big ^ Big;
};
signed main() { return 0; }
