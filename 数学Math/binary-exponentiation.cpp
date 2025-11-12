// {"name": "快速幂", "intro":"在 $O(log n)$ 的时间内求出 $a^n mod p$ 的值。"}
using ll = long long;
ll qpow(ll a, ll b, ll M) {
    ll ret = 1;
    for (a %= M; b; b >>= 1, a = a * a % M)
        if (b & 1) ret = ret * a % M;
    return ret;
}
