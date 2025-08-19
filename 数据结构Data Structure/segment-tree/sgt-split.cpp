#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m, root[N << 2], rcnt = 1, rub[N << 5], cnt, nodecnt;
struct treenode
{
 int ls, rs, sum;
} tr[N << 5];
inline int newnode() { return cnt ? rub[cnt--] : ++nodecnt; }
inline void del(int &p) { tr[p].ls = tr[p].rs = tr[p].sum = 0, rub[++cnt] = p, p = 0; }
inline void push_up(int p) { tr[p].sum = tr[tr[p].ls].sum + tr[tr[p].rs].sum; }
inline void build(int &p, int pl, int pr)
{
 if (!p) p = newnode();
 if (pl == pr) return cin >> tr[p].sum, void();
 int mid = (pl + pr) >> 1;
 build(tr[p].ls, pl, mid), build(tr[p].rs, mid + 1, pr);
 push_up(p);
}
inline void update(int &p, int pl, int pr, int pos, int k)
{
 if (!p) p = newnode();
 if (pl == pr) return tr[p].sum += k, void();
 int mid = (pl + pr) >> 1;
 if (pos <= mid) update(tr[p].ls, pl, mid, pos, k);
 else update(tr[p].rs, mid + 1, pr, pos, k);
 push_up(p);
}
inline int merge(int p, int q, int pl, int pr)
{
 if (!p || !q) return p + q;
 if (pl == pr) return tr[p].sum += tr[q].sum, del(q), p;
 int mid = (pl + pr) >> 1;
 tr[p].ls = merge(tr[p].ls, tr[q].ls, pl, mid);
 tr[p].rs = merge(tr[p].rs, tr[q].rs, mid + 1, pr);
 return push_up(p), del(q), p;
}
inline void split(int &p, int &q, int pl, int pr, int L, int R)
{
 if (R < pl || L > pr) return;
 if (!p) return;
 if (L <= pl && pr <= R) return q = p, p = 0, void();
 int mid = (pl + pr) >> 1;
 if (!q) q = newnode();
 if (L <= mid) split(tr[p].ls, tr[q].ls, pl, mid, L, R);
 if (R > mid) split(tr[p].rs, tr[q].rs, mid + 1, pr, L, R);
 push_up(p), push_up(q);
}
inline int query(int p, int pl, int pr, int L, int R)
{
 if (!p) return 0;
 if (L <= pl && pr <= R) return tr[p].sum;
 int mid = (pl + pr) >> 1, res = 0;
 if (L <= mid) res += query(tr[p].ls, pl, mid, L, R);
 if (R > mid) res += query(tr[p].rs, mid + 1, pr, L, R);
 return res;
}
inline int kth(int p, int pl, int pr, int k)
{
 if (pl == pr) return pl;
 int mid = (pl + pr) >> 1, left = tr[tr[p].ls].sum;
 if (k <= left) return kth(tr[p].ls, pl, mid, k);
 else return kth(tr[p].rs, mid + 1, pr, k - left);
}
signed main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 cin >> n >> m;
 build(root[1], 1, n);
 for (int i = 1, op, p, x, y; i <= m; i++)
 {
  cin >> op >> p >> x;
  if (op == 0 || op == 2 || op == 3) cin >> y;
  if (op == 0) split(root[p], root[++rcnt], 1, n, x, y);
  else if (op == 1) root[p] = merge(root[p], root[x], 1, n);
  else if (op == 2) update(root[p], 1, n, y, x);
  else if (op == 3) cout << query(root[p], 1, n, x, y) << "\n";
  else if (op == 4)
  {
   if (tr[root[p]].sum < x) cout << "-1\n";
   else cout << kth(root[p], 1, n, x) << "\n";
  }
 }
 return 0;
}