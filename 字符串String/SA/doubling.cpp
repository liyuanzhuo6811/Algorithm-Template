// {"name": "倍增法", "intro": "$O(n \log n)$ 时间内求 SA。我说白了你们不能搞点正常的东西上来吗？？？"}
#include <iostream>
#include <utility>
using namespace std;
const int N = 3e5 + 10;
int cnt[N], sa[N], rk[N], tmp[N], height[N];
inline void Radix_Sort(int n, int m) {
    for (int i = 1; i <= m; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cnt[rk[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) {
        sa[cnt[rk[tmp[i]]]] = tmp[i];
        cnt[rk[tmp[i]]]--;
    }
}
inline void BuildSA(const string &s) {
    int m = 255, n = s.size();
    for (int i = 1; i <= n; i++) {
        rk[i]  = s[i - 1];
        tmp[i] = i;
    }
    Radix_Sort(n, m);
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n; i > n - k; i--) tmp[++p] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > k) tmp[++p] = sa[i] - k;
        Radix_Sort(n, m);
        swap(tmp, rk);
        rk[sa[1]] = (p = 1);
        for (int i = 2; i <= n; i++) {
            if (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + k] == tmp[sa[i - 1] + k]) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
        }
        m = p;
    }
}
inline void BuildHeight(const string &s) {
    int n     = s.size(), k = 0;
    height[1] = 0;
    for (int i = 1; i <= n; i++) {
        if (rk[i] == 1) continue;
        int &nw = height[rk[i]];
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (k + max(i, j) <= n && s[i + k - 1] == s[j + k - 1]) k++;
        nw = k;

    }
}
int main() {
    string s;
    cin >> s;
    BuildSA(s);
    BuildHeight(s);
    int n = s.size();
    for (int i = 1; i <= n; i++) cout << sa[i] - 1 << " ";
    cout << endl;
    for (int i = 1; i <= n; i++) cout << height[i] << " ";
    cout << endl;
}