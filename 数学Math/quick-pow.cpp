/*
可以在 O(log n) 的时间内求出a^b%p的值。

不需要任何头文件。

最初编辑人：01bit
最后修改人：SnowFlavour
*/

using ll = long long;
ll p;
ll qpow(ll x, ll y) {
    ll z = 1;
    while (y) {
        if (y & 1) z = z * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return z;
}