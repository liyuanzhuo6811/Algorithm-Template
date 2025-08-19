const int N = 1e5 + 5;
int rt, siz[N], ch[N][2], val[N], tot, fa[N], cnt[N];
void pushup(int p) { siz[p] = siz[ch[p][0]] + siz[ch[p][1]] + cnt[p]; }
bool get(int p) { return p == ch[fa[p]][1]; }
void clear(int p) { siz[p] = ch[p][0] = ch[p][1] = val[p] = fa[p] = cnt[p] = 0; }
void rotate(int p)
{
 int f = fa[p], g = fa[f], chk = get(p);
 ch[f][chk] = ch[p][chk ^ 1];
 if (ch[p][chk ^ 1]) fa[ch[p][chk ^ 1]] = f;
 ch[p][chk ^ 1] = f, fa[f] = p, fa[p] = g;
 if (g) ch[g][f == ch[g][1]] = p;
 pushup(f), pushup(p);
}
void splay(int p)
{
 for (int f = fa[p]; f = fa[p], f; rotate(p))
  if (fa[f]) rotate(get(p) == get(f) ? f : p);
 rt = p;
}

void nw(int k, int fath, int op) { val[++tot] = k, siz[tot] = cnt[tot] = 1, fa[tot] = fath, ch[fath][op] = tot; }
void ins(int k)
{
 if (!rt)
 {
  val[++tot] = k, cnt[tot]++, rt = tot;
  return pushup(rt);
 }
 int cur = rt, f = 0;
 while (1)
 {
  if (val[cur] == k)
  {
   cnt[cur]++;
   pushup(cur), pushup(f), splay(cur);
   break;
  }
  f = cur, cur = ch[cur][val[cur] < k];
  if (!cur)
  {
   val[++tot] = k;
   cnt[tot]++, fa[tot] = f, ch[f][val[f] < k] = tot;
   pushup(tot), pushup(f), splay(tot);
   break;
  }
 }
}
int rk(int k)
{
 int p = rt, res = 0;
 while (true)
 {
  if (k < val[p]) p = ch[p][0];
  else
  {
   res += siz[ch[p][0]];
   if (!p) return res + 1;
   if (val[p] == k) return splay(p), res + 1;
   res += cnt[p], p = ch[p][1];
  }
 }
}
int prev()
{
 int p = ch[rt][0];
 if (!p) return p;
 while (ch[p][1]) p = ch[p][1];
 return splay(p), p;
}
int next()
{
 int p = ch[rt][1];
 if (!p) return p;
 while (ch[p][0]) p = ch[p][0];
 return splay(p), p;
}
void del(int k)
{
 rk(k);
 if (cnt[rt] > 1) return --cnt[rt], pushup(rt), void();
 if (!ch[rt][0] && !ch[rt][1]) return clear(rt), rt = 0, void();
 if (!ch[rt][0])
 {
  int cur = rt;
  rt = ch[rt][1], fa[rt] = 0;
  clear(cur);
  return;
 }
 if (!ch[rt][1])
 {
  int cur = rt;
  rt = ch[rt][0], fa[rt] = 0;
  clear(cur);
  return;
 }
 int cur = rt, x = prev();
 fa[ch[cur][1]] = x, ch[x][1] = ch[cur][1];
 clear(cur), pushup(rt);
}
int kth(int k)
{
 int p = rt;
 while (1)
 {
  if (ch[p][0] && k <= siz[ch[p][0]]) p = ch[p][0];
  else
  {
   k -= cnt[p] + siz[ch[p][0]];
   if (k <= 0) return splay(p), val[p];
   p = ch[p][1];
  }
 }
}