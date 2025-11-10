// {"name":"轮廓线 DP","intro":"逐格 DP，记录会影响后面格子的状态，即轮廓线。题目为 https://atcoder.jp/contests/typical90/tasks/typical90_w。"}
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
const int mod = 1e9 + 7;
const int N = 24 + 5;
int h, w;
string s[N];
#define clr(x, i) ((i) < 0 || w < (i) ? x : x & (~0 ^ (1 << (i))))
#define add(x, i) ((i) < 0 || w < (i) ? x : x | (1 << (i)))
#define tak(x, i) ((i) < 0 || w < (i) ? 0 : x & (1 << (i)))
unordered_map<int, int> f, g;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> h >> w;
    for (int i = 0; i < h; i++) cin >> s[i];
    f[0] = 1;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            swap(f, g);
            f.clear();
            for (const auto &p : g) {
                int x = p.first, k = p.second;
                int y = clr(x, j), z = add(x, j);
                if (j == w - 1) (f[clr(y, w) << 1] += k) %= mod;
                else (f[y] += k) %= mod;
                if (s[i][j] == '.' && !tak(x, j - 1) && !tak(x, j) && !tak(x, j + 1) && !tak(x, j + 2)) {
                    if (j == w - 1) (f[clr(z, w) << 1] += k) %= mod;
                    else (f[z] += k) %= mod;
                }
            }
        }
    int ans = 0;
    for (const auto &p : f) (ans += p.second) %= mod;
    cout << ans;
    return 0;
}
