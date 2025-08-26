// {"name": "求欧拉函数", "intro": "在 $O(\log n)$ 的时间复杂度内求出一个数的欧拉函数。"}
#include <cmath>
int euler_phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}
int main() { return 0; }