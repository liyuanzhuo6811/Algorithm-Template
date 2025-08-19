#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#define int long long
using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
int n, m, seed, vmax, a[N];
int rnd()
{
 int ret = seed;
 seed = (seed * 7 + 13) % mod;
 return ret;
}
int qpow(int a, int b, int Mod)
{
 long long res = 1;
 a %= Mod;
 while (b)
 {
  if (b & 1) res = res * a % Mod;
  a = a * a % Mod, b >>= 1;
 }
 return res;
}
struct node
{
 int l, r;
 mutable int v;
 node(const int &ll, const int &rr, const int &vv) : l(ll), r(rr), v(vv) {}
 bool operator<(const node &b) const { return l < b.l; }
};
set<node> st;
typedef set<node>::iterator it;
it split(int x)
{
 if (x > n) return st.end();
 it I = st.lower_bound((node){x, 0, 0});
 if (I != st.end() && I->l == x) return I;
 I--;
 if (I->r < x) return st.end();
 int l = I->l, r = I->r, v = I->v;
 st.erase(I);
 st.insert(node(l, x - 1, v));
 return st.insert(node(x, r, v)).first;
}
void assign(int l, int r, int v)
{
 it itr = split(r + 1), itl = split(l);
 st.erase(itl, itr);
 st.insert(node(l, r, v));
}
vector<pair<int, int>> tmp;
signed main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 cin >> n >> m >> seed >> vmax;
 for (int i = 1; i <= n; i++)
 {
  a[i] = rnd() % vmax + 1;
  st.insert(node(i, i, a[i]));
 }
 for (int at = 1, op, l, r, x, y, ans; at <= m; at++)
 {
  op = (rnd() % 4) + 1;
  l = (rnd() % n) + 1;
  r = (rnd() % n) + 1;
  if (l > r) swap(l, r);
  if (op == 1)
  {
   x = rnd() % vmax + 1;
   it itr = split(r + 1), itl = split(l);
   for (; itl != itr; ++itl) itl->v += x;
  }
  else if (op == 2)
  {
   x = rnd() % vmax + 1;
   assign(l, r, x);
  }
  else if (op == 3)
  {
   x = rnd() % (r - l + 1) + 1;
   tmp.clear();
   it itr = split(r + 1), itl = split(l);
   for (it I = itl; I != itr; ++I) tmp.push_back({I->v, I->r - I->l + 1});
   sort(tmp.begin(), tmp.end());
   ans = -1;
   for (int i = 0; i < tmp.size(); i++)
   {
    x -= tmp[i].second;
    if (x <= 0)
    {
     ans = tmp[i].first;
     break;
    }
   }
   cout << ans << '\n';
  }
  else
  {
   ans = 0;
   x = rnd() % vmax + 1;
   y = rnd() % vmax + 1;
   it itr = split(r + 1), itl = split(l);
   for (it I = itl; I != itr; ++I) ans = (ans + qpow(I->v, x, y) * (I->r - I->l + 1) % y) % y;
   cout << ans << '\n';
  }
 }
 return 0;
}