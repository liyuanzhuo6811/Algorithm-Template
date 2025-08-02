#include <iostream>
using namespace std;
typedef long long ll;
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
int main() {
    ll a, b;
    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << qpow(a, b);
    return 0;
}