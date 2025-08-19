#include <bits/stdc++.h>
using namespace std;
struct dsu
{
 vector<size_t> pa, size;
 explicit dsu(size_t size_) : pa(size_), size(size_, 1) { iota(pa.begin(), pa.end(), 0); }
 inline size_t find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
 void unite(size_t x, size_t y)
 {
  x = find(x), y = find(y);
  if (x == y) return;
  if (size[x] < size[y]) swap(x, y);
  pa[y] = x;
  size[x] += size[y];
 }
 void erase(size_t x) { --size[find(x)], pa[x] = x; }
 void dsu::move(size_t x, size_t y)
 {
  auto fx = find(x), fy = find(y);
  if (fx == fy) return;
  pa[x] = fy;
  --size[fx], ++size[fy];
 }
};
