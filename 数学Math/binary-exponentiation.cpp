// {"name": "快速幂", "intro": "在 $O(\log n)$ 的时间内求出 $a^n \bmod p$ 的值。"}
using ll = long long;
inline ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    if (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res % mod;
}
int main() { return 0; }