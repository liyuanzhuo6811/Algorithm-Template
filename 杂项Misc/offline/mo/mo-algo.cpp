void move(int pos, int sign) { ... }
int unit;
struct node
{
 int l, r, id;
 bool operator<(const node &x) const
 {
  return l / unit == x.l / unit ? (r == x.r ? 0 : ((l / unit) & 1) ^ (r < x.r)) : l < x.l;
 }
} querys[N];
void solve()
{
 unit = int(ceil(pow(n, 0.5)));
 sort(querys, querys + m);
 for (int i = 0; i < m; ++i)
 {
  const node &q = querys[i];
  while (l > q.l) move(--l, 1);
  while (r < q.r) move(++r, 1);
  while (l < q.l) move(l++, -1);
  while (r > q.r) move(r--, -1);
  ans[q.id] = nowAns;
 }
}