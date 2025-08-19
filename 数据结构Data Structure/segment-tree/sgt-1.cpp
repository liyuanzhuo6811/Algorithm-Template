#include <iostream>
using namespace std;
using ll = long long;
namespace segment_tree
{
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (pl + pr >> 1)
const int N = 1e6 + 5;
int sum[N], tag[N];
inline void up(int p) { sum[p] = sum[ls] + sum[rs]; }
inline void spread(int p, int pl, int pr)
{
 if (!tag[p]) return;
 tag[ls] += tag[p], tag[rs] += tag[p];
 sum[ls] += tag[p] * (mid - pl + 1), sum[rs] += tag[p] * (pr - mid);
 tag[p] = 0;
}
void build(int p, int pl, int pr, int *a)
{
 if (pl == pr) return sum[p] = a[pl], void();
 build(ls, pl, mid, a), build(rs, mid + 1, pr, a), up(p);
}
void update(int p, int pl, int pr, int L, int R, int v)
{
 if (L <= pl && pr <= R) return sum[p] += v, void();
 spread(p, pl, pr);
 if (L <= mid) update(ls, pl, mid, L, R, v);
 if (R > mid) update(rs, mid + 1, pr, L, R, v);
 up(p);
}
int query(int p, int pl, int pr, int L, int R)
{
 if (L <= pl && pr <= R) return sum[p];
 spread(p, pl, pr);
 int res(0);
 if (L <= mid) res += query(ls, pl, mid, L, R);
 if (R > mid) res += query(rs, mid + 1, pr, L, R);
 return res;
}
}; // namespace segment_tree
int main() { return 0; }