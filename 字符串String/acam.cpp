// {"name": "AC自动机", "intro": "自动 ac"}
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
namespace acam {
const int SIZ = 2000005;
struct node {
    int ch[26], fail, ans, id;
    node() { memset(ch, 0, sizeof(ch)), ans = id = 0; }
    inline int &operator[](const int x) { return x < 26 ? ch[x] : ch[x - 'a']; }
    inline int operator[](const int x) const { return x < 26 ? ch[x] : ch[x - 'a']; }
} tr[SIZ];
int tot, ans[SIZ], pcnt;
vector<int> fail[SIZ];
inline void insert(char *s, int &id) {
    int u = 0;
    for (int i = 1; s[i]; i++) {
        if (!tr[u][i]) tr[u][i] = ++tot;
        u = tr[u][i];
    }
    if (!tr[u].id) tr[u].id = ++pcnt;
    id = tr[u].id;
}
inline void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (tr[0][i]) q.push(tr[0][i]), fail[0].push_back(tr[0][i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u][i]) {
                tr[tr[u][i]].fail = tr[tr[u].fail][i];
                fail[tr[tr[u].fail][i]].push_back(tr[u][i]);
                q.push(tr[u][i]);
            } else tr[u][i] = tr[tr[u].fail][i];
        }
    }
}
void query(char *t) {
    int u = 0;
    for (int i = 1; t[i]; ++i) u = tr[u][t[i]], tr[u].ans++;
}
void dfs(int u) {
    for (int v : fail[u]) {
        dfs(v);
        tr[u].ans += tr[v].ans;
    }
    ans[tr[u].id] = tr[u].ans;
}
}; // namespace acam
int main() { return 0; }