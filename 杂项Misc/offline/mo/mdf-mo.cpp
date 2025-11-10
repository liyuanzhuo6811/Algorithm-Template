// {"name": "带修莫队", "intro": "在 $O(n^{\frac{5}{3}})$ 次方内解决可回滚的修改问题。"}

for (int sz = max(1.0, pow(n, 2.0 / 3)), i = 1; i <= n; i++) bl[i] = (i - 1) / sz + 1;
sort(q + 1, q + n + 1, [](oper a, oper b) {
    auto [x, y, t, ida] = a;
    auto [xx, yy, tt, idb] = b;
    if (bl[x] != bl[xx]) return x < xx;
    if (bl[y] != bl[yy]) return y < yy;
    return t < tt;
});
int L = 1, R = 0, ti = 0, ans = 0;
auto add = [&](int x) { b[x]++, ans += b[x] == 1; };
auto del = [&](int x) { b[x]--, ans -= b[x] == 0; };
auto mo = [&add, &del](int x, int i) {
    auto &[p, y] = m[x];
    auto [l, r, t, id] = q[i];
    if (l <= p && p <= r) del(a[p]), add(y);
    swap(a[p], y);
};
for (int i = 1; i <= n; i++) {
    auto [l, r, t, id] = q[i];
    while (L > l) add(a[--L]);
    while (R < r) add(a[++R]);
    while (L < l) del(a[L++]);
    while (R > r) del(a[R--]);
    while (ti < t) mo(++ti, i);
    while (ti > t) mo(ti--, i);
    res[id] = ans;
}