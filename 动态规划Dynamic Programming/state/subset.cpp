// {"name":"子集枚举","intro":"时间复杂度 $O(n3^m)$"}
#include <bits/stdc++.h>
using namespace std;
const int N = 26, mod = 1e9 + 7;
int n, m, E[N];
char s[N][N];
size_t dp[2][(1 << 24) + 5];
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
    auto check = [&](int S, int T, int x) -> bool {
        if (S & T) return false;
        if (T & (T << 1)) return false;
        if ((S << 1) & T) return false;
        if ((S >> 1) & T) return false;
        if (T & E[x]) return false;
        return true;
    };
    int cur = 0, pre = 1;
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        swap(pre, cur), memset(dp[cur], 0, sizeof(dp[cur]));
        for (int S = 0; S < (1 << m); ++S) dp[cur][0] += dp[pre][S];
        for (int S = 0, Sn; S < (1 << m); ++S) {
            if (!dp[pre][S]) continue;
            Sn = ((1 << m) - 1) ^ S;
            for (int T = Sn; T; T = (T - 1) & Sn)
                if (check(S, T, i)) (dp[cur][T] += dp[pre][S]) %= mod;
        }
    }
    size_t ans = 0;
    for (int S = 0; S < (1 << m); ++S) (ans += dp[cur][S]) %= mod;
    cout << ans << endl;
    return 0;
}