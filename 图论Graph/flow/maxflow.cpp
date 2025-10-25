// {"name": "dinic 算法", "intro": "求最大流"}
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define int long long
using namespace std;
const int N=205,M=5005;
int n,m,s,t,head[N],tot=-1;
struct edge{
	int v,w,nxt;
}e[M<<1];
inline void add(int u,int v,int w)
{
	e[++tot].v=v,e[tot].w=w;
	e[tot].nxt=head[u],head[u]=tot;
}
int dis[N],cur[N];
queue<int> q;
inline bool bfs()
{
	for(int i=1;i<=n;i++)dis[i]=-1;
	dis[s]=0;q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];~i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(dis[v]==-1&&e[i].w)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t]!=-1;
}
int dfs(int u,int minf)
{
	if(!minf||u==t)return minf;
	int fsum=0,flow;
	for(int i=cur[u];~i;i=e[i].nxt)
	{
		int v=e[i].v;
		cur[u]=i;
		if(dis[v]==dis[u]+1&&(flow=dfs(v,min(e[i].w,minf))))
		{
			e[i].w-=flow,e[i^1].w+=flow;
			minf-=flow,fsum+=flow;
			if(!minf)return fsum;
		}
	}
	return fsum;
}
inline int Dinic()
{
	int maxflow=0;
	while(bfs())
	{
		for(int i=1;i<=n;i++)cur[i]=head[i];
		maxflow+=dfs(s,0x7f7f7f7f);
	}
	return maxflow;
}
signed main()
{
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w);add(v,u,0);
	}
	cout<<Dinic()<<endl;
	return 0;
}