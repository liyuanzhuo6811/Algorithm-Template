#include <cstdio>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], tot;
int root[N], cnt;
struct node
{
 int ls, rs;
 int val;
} tree[N * 30];
int build(int pl, int pr)
{
 int rt = tot++;
 if (pl == pr)
 {
  tree[rt].val = a[pl];
  return rt;
 }
 int mid = (pl + pr) >> 1;
 tree[rt].ls = build(pl, mid);
 tree[rt].rs = build(mid + 1, pr);
 return rt;
}
int update(int pre, int pl, int pr, int loc, int val)
{
 int rt = tot++;
 if (pl == pr)
 {
  tree[rt].val = val;
  return rt;
 }
 int mid = (pl + pr) >> 1;
 tree[rt].ls = tree[pre].ls;
 tree[rt].rs = tree[pre].rs;
 if (loc <= mid) tree[rt].ls = update(tree[pre].ls, pl, mid, loc, val);
 else tree[rt].rs = update(tree[rt].rs, mid + 1, pr, loc, val);
 return rt;
}
int query(int p, int pl, int pr, int loc)
{
 if (pl == pr) return tree[p].val;
 int mid = (pl + pr) >> 1;
 if (loc <= mid) return query(tree[p].ls, pl, mid, loc);
 else return query(tree[p].rs, mid + 1, pr, loc);
}
int main()
{
 scanf("%d%d", &n, &m);
 for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
 root[cnt++] = build(1, n);
 while (m--)
 {
  int v, op, loc, val;
  scanf("%d%d%d", &v, &op, &loc);
  if (op == 1)
  {
   scanf("%d", &val);
   root[cnt++] = update(root[v], 1, n, loc, val);
  }
  else
  {
   root[cnt++] = root[v];
   int res = query(root[v], 1, n, loc);
   printf("%d\n", res);
  }
 }
 return 0;
}