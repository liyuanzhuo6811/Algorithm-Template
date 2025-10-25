// {"name": "SSP 算法", "intro": "不能有负环，求最小费用最大流"}
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int N=5005,M=50005,INF=1e9;
int n,m,s,t,head[N],tot=1;
struct edge{
	int v,nxt,w,c;
}e[M<<1];
inline void add(int u,int v,int w,int c){e[++tot]={v,head[u],w,c},head[u]=tot;}
int d[N],cur[N],mincost,maxflow;
bool vis[N];
inline bool spfa(int s,int t)
{
	queue<int> q;
	for(int i=1;i<=n;i++)d[i]=INF,vis[i]=false;
	q.push(s),d[s]=0,vis[s]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop(),vis[u]=false;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(d[v]>d[u]+e[i].c&&e[i].w)
			{
				d[v]=d[u]+e[i].c;
				if(!vis[v]) q.push(v),vis[v]=true;
			}
		}
	}
	return d[t]!=INF;
}
int dfs(int u,int minf)
{
	if(u==t||!minf) return minf;
	int flow=0,f;
	vis[u]=true;
	for(int i=cur[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(!vis[v]&&e[i].w&&d[v]==d[u]+e[i].c)
		{
			f=dfs(v,min(minf,e[i].w));
			if(f)
			{
				e[i].w-=f,e[i^1].w+=f,minf-=f,flow+=f;
				mincost+=f*e[i].c;
				if(!minf)return vis[u]=false,flow;
			}
		}
	}
	return vis[u]=false,flow;
}
inline void solve()
{
	mincost=maxflow=0;
	while(spfa(s,t))
	{
		for(int i=1;i<=n;i++)cur[i]=head[i];
		maxflow+=dfs(s,INF);
	}
}
int main()
{
	cin.tie(0)->sync_with_stdio(false);
	cout.tie(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++)
	{
		int u,v,w,c;
		cin>>u>>v>>w>>c;
		add(u,v,w,c),add(v,u,0,-c);
	}
	solve();
	cout<<maxflow<<' '<<mincost<<'\n';
	return 0; 
}