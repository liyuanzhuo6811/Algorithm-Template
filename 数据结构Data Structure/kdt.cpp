// {"name": "KD-Tree", "intro": "到时候看见一个高维问题不是数数直接拿KDT操——lhc0707"}
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, K = 20;
using pt = array<int, K>;
bool operator<=(const pt &a, const pt &b)
{ 
 for (int i = 0 ; i < K; ++i) if (a[i] > b[i]) return false;
 return true;
}
bool operator<(const pt &a, const pt &b)
{
 for (int i = 0; i < K; ++i) if (a[i] >= b[i]) return false;
 return true;
}
int n, k, rt[K], m, cnt;
struct info {} I0, a[N];
struct Tag {} T0;
info operator+(const info &a, const info &b) { ; }
info operator+(const info &a, const Tag &b) { ; }
Tag operator+(const Tag &a, const Tag &b) { ; }
bool operator==(const Tag &a, const Tag &b) { return true; }
struct treenode
{
 int lc, rc;
 pt mx, mn, now;
 info t = I0, sum = I0;
 Tag tag = T0;
} tr[N];
pt p[N];
inline void up(int rt)
{
 tr[rt].mx = tr[rt].mn = tr[rt].now, tr[rt].sum = tr[rt].t;
 if (tr[rt].lc) 
 {
  tr[rt].sum = tr[rt].sum + tr[tr[rt].lc].sum;
  for (int i = 0; i < k; ++i) tr[rt].mx[i] = max(tr[rt].mx[i], tr[tr[rt].lc].mx[i]);
  for (int i = 0; i < k; ++i) tr[rt].mn[i] = min(tr[rt].mn[i], tr[tr[rt].lc].mn[i]);
 }
 if (tr[rt].rc)
 {
  tr[rt].sum = tr[rt].sum + tr[tr[rt].rc].sum;
  for (int i = 0; i < k; ++i) tr[rt].mx[i] = max(tr[rt].mx[i], tr[tr[rt].rc].mx[i]);
  for (int i = 0; i < k; ++i) tr[rt].mn[i] = min(tr[rt].mn[i], tr[tr[rt].rc].mn[i]);
 }
}
inline void spread(int rt)
{
 if (tr[rt].tag == T0) return;
 tr[tr[rt].lc].t = tr[tr[rt].lc].t + tr[rt].tag;
 tr[tr[rt].rc].t = tr[tr[rt].rc].t + tr[rt].tag;
 tr[tr[rt].lc].sum = tr[tr[rt].lc].sum + tr[rt].tag;
 tr[tr[rt].rc].sum = tr[tr[rt].rc].sum + tr[rt].tag;
 tr[tr[rt].lc].tag = tr[tr[rt].lc].tag + tr[rt].tag;
 tr[tr[rt].rc].tag = tr[tr[rt].rc].tag + tr[rt].tag;
 tr[rt].tag = T0;
}
int build(int pl, int pr, int d = 0)
{
 if (pl > pr) return 0;
 int mid = (pl + pr) >> 1, rt = mid;
 nth_element(p + pl, p + mid, p + pr + 1, [d](pt i, pt j) { return i[d] < j[d]; });
 tr[rt].now = p[mid], tr[rt].t = a[mid];
 tr[rt].lc = build(pl, mid - 1, (d + 1) % k);
 tr[rt].rc = build(mid + 1, pr, (d + 1) % k);
 return up(rt), rt;
}
void update(int rt, pt L, pt R, Tag d)
{
 if (L <= tr[rt].mn && tr[rt].mx <= R)
 {
  tr[rt].t = tr[rt].t + d;
  tr[rt].tag = tr[rt].tag + d;
  tr[rt].sum = tr[rt].sum + d;
  return;
 }
 if (tr[rt].mx < L || R < tr[rt].mn) return;
 spread(rt);
 if (L <= tr[rt].now && tr[rt].now <= R) tr[rt].t = tr[rt].t + d, tr[rt].tag = tr[rt].tag + d;
 if (tr[rt].lc) update(tr[rt].lc, L, R, d);
 if (tr[rt].rc) update(tr[rt].rc, L, R, d);
 up(rt);
}
info query(int rt, pt L, pt R)
{
 if (!rt || tr[rt].mx < L || R < tr[rt].mn) return I0;
 if (L <= tr[rt].mn && tr[rt].mx <= R) return tr[rt].sum;
 spread(rt);
 info ans = I0;
 if (L <= tr[rt].now && tr[rt].now <= R) ans = tr[rt].t;
 return query(tr[rt].lc, L, R) + ans + query(tr[rt].rc, L, R);
}
void append(int &rt)
{
 if (!rt) return;
 p[++cnt] = tr[rt].now;
 append(tr[rt].lc), append(tr[rt].rc);
 rt = 0;
}
signed main() 
{
 cin >> n >> k >> m;
 for (int i = 1; i <= n; ++i) 
  for (int j = 0; i < k; ++j) cin >> p[i][j];
 build(1, n);
 // dynamic build
 while (m--)
 {
  pt now;
  for (int j = 0; j < k; ++j) cin >> now[j];
  p[cnt = 1] = now;
  for (int sz = 0; true; ++sz)
   if (!rt[sz])
   {
    rt[sz] = build(1, cnt);
    break;
   }
   else append(rt[sz]);
 }
 return 0; 
}