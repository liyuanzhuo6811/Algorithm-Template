// {"name":"最终优化","intro":"把压缩状态集合和轮廓线结合起来，$O(nmfib(m))$"}
#include <bits/stdc++.h>
using namespace std;
const int N = 26, mod = 1e9 + 7;
int n, m, E[N], k, id[(1 << 24) + 5];
char s[N][N];
vector<int> st;
inline void dfs(int i, int S, int U, const vector<size_t> &dp, size_t &sum) {
    if (i >= m) {
        (sum += dp[id[S]]) %= mod;
        return;
    }
    dfs(i + 1, S, U, dp, sum);
    if ((U >> i) & 1)
        if (i == 0 || !(S & (1 << i - 1))) dfs(i + 1, S | (1 << i), U, dp, sum);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        for (int j = 0; j < m; ++j)
            if (s[i][j] == '#') E[i] |= (1 << j);
    }

    for (int i = 0; i < (1 << m); ++i) id[i] = -1;
    for (int S = 0; S < (1 << m); ++S)
        if (!(S & (S << 1))) st.push_back(S), ++k;
    for (int i = 0; i < k; ++i) id[st[i]] = i;

    vector<size_t> dp(k, 0);
    for (int S : st)
        if ((S & E[1]) == 0) dp[id[S]] = 1;

    for (int i = 2; i <= n; ++i) {
        vector<size_t> dp_new(k, 0);
        for (int S : st) {
            if ((S & E[i])) continue;
            int U = S | (S << 1) | (S >> 1);
            U &= (1 << m) - 1, U = ~U & ((1 << m) - 1);
            size_t sum = 0;
            dfs(0, 0, U, dp, sum);
            dp_new[id[S]] = sum;
        }
        dp = dp_new;
    }

    size_t ans = 0;
    for (int i = 0; i < k; ++i) (ans += dp[i]) %= mod;
    cout << ans << endl;
    return 0;
}