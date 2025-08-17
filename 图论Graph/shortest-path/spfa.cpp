/*
SPFA支持求单源最短路，支持负权，如果需要判断负环则需要添加 #define NEG_RING。
可以通过修改一些代码来支持最长/最大最小路等。
期望复杂度O(kn)，可能会退化成O(nm)。

需要以下头文件：
vector, queue, cstring

最初编辑人：SnowFlavour
最后修改人：SnowFlavour
*/
struct Edge {
    int v, w;
    Edge() {}
    Edge(int vv, int ww) : v(vv), w(ww) {}
    bool operator<(Edge x) const { return w < x.w; }
    bool operator>(Edge x) const { return w > x.w; }
};
const int N = 1e5 + 10;
vector<Edge> e[N];
int dis[N];
bool inq[N];
#ifdef NEG_RING
int cnt[N], n;
inline bool SPFA(int s) {
#else
inline void SPFA(int s) {
#endif
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    q.push(s);
    inq[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
#ifdef NEG_RING
        if (cnt[u] > n) return false;
#endif
        for (auto [v, w] : e[u]) {
            if (inq[v]) continue;
            if (dis[u] + w < dis[v]) {
                q.push(v);
                dis[v] = dis[u] + w;
#ifdef NEG_RING
                cnt[v]++;
#endif
            }
        }
    }
#ifdef NEG_RING
    return true;
#endif
}