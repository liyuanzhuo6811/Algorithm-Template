/*
Dijkstra支持求单源最短路，不支持负权。
可以通过修改一些代码来支持最长/最大最小路等。

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
int dis[N];
bool vis[N];
vector<Edge> e[N];
inline void Dijkstra(int s) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> q; // 通过将greater换成less可以实现最长路
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(Edge(s, 0));
    while (!q.empty()) {
        auto [u, now] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u]) {
            if (now + w < dis[v]) {                      // 改成max，min等可以支持最长路径最短等
                q.push(Edge(v, dis[v] = now + w));       // 这里同理
            }
        }
    }
}