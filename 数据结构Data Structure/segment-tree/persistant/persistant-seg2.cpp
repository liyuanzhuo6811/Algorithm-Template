#include <algorithm>
#include <cstdio>
#include <iostream>
#define endl '\n'
using std::cin;
using std::cout;
using std::lower_bound;
using std::sort;
using std::unique;
const int N = 2e5 + 5;
int n, m, a[N], b[N], size, tot;
int root[N], vcnt;
struct node
{
 int l, r;
 int sum;
} tree[N * 30];
int build(int pl, int pr)
{
 int rt = ++tot;
 tree[rt].sum = 0;
 int mid = (pl + pr) >> 1;
 if (pl < pr)
 {
  tree[rt].l = build(pl, mid);
  tree[rt].r = build(mid + 1, pr);
 }
 return rt;
}
int update(int pre, int pl, int pr, int x)
{
 int rt = ++tot;
 tree[rt].l = tree[pre].l;
 tree[rt].r = tree[pre].r;
 tree[rt].sum = tree[pre].sum + 1;
 int mid = (pl + pr) >> 1;
 if (pl < pr)
 {
  if (x <= mid) tree[rt].l = update(tree[pre].l, pl, mid, x);
  else tree[rt].r = update(tree[pre].r, mid + 1, pr, x);
 }
 return rt;
}
int query(int u, int v, int pl, int pr, int k)
{
 if (pl == pr) return pl;
 int x = tree[tree[v].l].sum - tree[tree[u].l].sum;
 int mid = (pl + pr) >> 1;
 if (x >= k) return query(tree[u].l, tree[v].l, pl, mid, k);
 else return query(tree[u].r, tree[v].r, mid + 1, pr, k - x);
}
int main()
{
 cin >> n >> m;
 for (int i = 1; i <= n; i++)
 {
  cin >> a[i];
  b[i] = a[i];
 }
 sort(b + 1, b + 1 + n);
 size = unique(b + 1, b + 1 + n) - (b + 1);
 root[0] = build(1, size);
 for (int i = 1; i <= n; i++)
 {
  int x = lower_bound(b + 1, b + 1 + size, a[i]) - b;
  root[i] = update(root[i - 1], 1, size, x);
 }
 while (m--)
 {
  int l, r, k;
  cin >> l >> r >> k;
  int res = query(root[l - 1], root[r], 1, size, k);
  cout << b[res] << endl;
 }
 return 0;
}