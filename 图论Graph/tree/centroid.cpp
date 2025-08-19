int size[MAXN], weight[MAXN], centroid[2];
void GetCentroid(int cur, int fa)
{
 size[cur] = 1, weight[cur] = 0;
 for (int i = head[cur]; i != -1; i = e[i].nxt)
 {
  if (e[i].to != fa)
  {
   GetCentroid(e[i].to, cur);
   size[cur] += size[e[i].to];
   weight[cur] = max(weight[cur], size[e[i].to]);
  }
 }
 weight[cur] = max(weight[cur], n - size[cur]);
 if (weight[cur] <= n / 2) centroid[centroid[0] != 0] = cur;
}