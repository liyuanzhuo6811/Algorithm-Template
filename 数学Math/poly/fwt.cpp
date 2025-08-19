#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define gi int, vector<int>, greater<int>
#define IOS cin.tie(0)->sync_with_stdio(false), cout.tie(0)
#define fo(i, begin, end)                                                                                              \
 for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
using namespace std;
using namespace __gnu_pbds;
using db = double;
using ll = long long;
using lint = __int128;
using pdd = pair<db, db>;
using pll = pair<ll, ll>;
using pdl = pair<db, ll>;
using pdi = pair<db, int>;
using pil = pair<int, ll>;
using pii = pair<int, int>;
using ull = unsigned ll;
using uint = unsigned int;
inline lint read()
{
 lint x = 0;
 bool f = 0;
 char c = getchar();
 while (c < '0' || c > '9') f = (c == '-'), c = getchar();
 while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
 return f ? -x : x;
}
void write(lint x)
{
 if (x < 0) { putchar('-'), x = -x; }
 if (x > 9) write(x / 10);
 putchar(x % 10 + '0');
}
const db eps = 1e-10, PI = acos(-1.0);
const ll mod = 998244353, MOD = 1e9 + 7, inv2 = 499122177;
const int N = (1 << 17) + 5;
const ll Cor[2][2] = {{1, 0}, {1, 1}};
const ll ICor[2][2] = {{1, 0}, {mod - 1, 1}};
const ll Cand[2][2] = {{1, 1}, {0, 1}};
const ll ICand[2][2] = {{1, mod - 1}, {0, 1}};
const ll Cxor[2][2] = {{1, 1}, {1, mod - 1}};
const ll ICxor[2][2] = {{inv2, inv2}, {inv2, mod - inv2}};
inline void FWT(ll *f, const ll c[2][2], int n)
{
 for (int len = 1; len < n; len <<= 1)
  for (int p = 0; p < n; p += len + len)
   for (int i = p; i < p + len; ++i)
   {
    int tmp = f[i];
    f[i] = (c[0][0] * f[i] + c[0][1] * f[i + len]) % mod;
    f[i + len] = (c[1][0] * tmp + c[1][1] * f[i + len]) % mod;
   }
}
inline void mul(ll *f, ll *g, const ll c[2][2], const ll ic[2][2], int n)
{
 FWT(f, c, n), FWT(g, c, n);
 fo(i, 0, n) f[i] = (f[i] * g[i]) % mod;
 FWT(f, ic, n);
}
int n;
ll a[N], b[N], f[N], g[N];
inline void work(const ll c[2][2], const ll ic[2][2])
{
 fo(i, 0, n) f[i] = a[i];
 fo(i, 0, n) g[i] = b[i];
 mul(f, g, c, ic, n);
 fo(i, 0, n) cout << f[i] << ' ';
 cout << '\n';
}
int main()
{
 IOS;
 cin >> n, n = (1 << n);
 fo(i, 0, n) cin >> a[i];
 fo(i, 0, n) cin >> b[i];
 work(Cor, ICor), work(Cand, ICand), work(Cxor, ICxor);
 return 0;
}