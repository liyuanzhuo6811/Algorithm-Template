// {"name": "欧拉筛法", "intro": "在 $O(n)$ 的时间内求出 $[1, n]$ 内的所有数的欧拉函数值。"}
#include <bitset>
using std::bitset;
const int N = 1e7 + 5;
bitset<N> not_prime;
int prime[N], pcnt, phi[N];
inline void sieve(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!not_prime[i]) prime[++pcnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= pcnt && i * prime[j] <= n; j++) {
            not_prime[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}
int main() { return 0; }