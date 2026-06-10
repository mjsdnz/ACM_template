#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+11;
int n,m;
int inx;
int cnt;
int w[maxn];
int son[maxn];
int fa[maxn];
int top[maxn];
vector <int> e_k[maxn];
int root[maxn];
int tot;
int Size[maxn];
int dnf[maxn];
int pre[maxn];


struct edge{
	int fr,to,v;
	bool operator <(const edge &a)const
	{
		return v < a.v;
	}
};
vector <edge> e;
void init()
{
	for(int i=1;i<=n;i++)
		pre[i] = i;
}
int find_p(int x)
{
	if(pre[x] == x)
		return x;
	pre[x] = find_p(pre[x]);
	return pre[x];
}
void add(int p,int c)
{
	p = find_p(p);
	pre[c] = p;
	return;
}
bool islink(int x,int y)
{
	if(find_p(x) == find_p(y))
		return true;
	return false;
}
void dfs1(int x,int p)
{
	fa[x] = p;
	Size[x]++;
	if(e_k[x].size() == 0)
	{
		return;
	}
	int max_son = 0 ;
	for(auto v:e_k[x])
	{ 
		
		dfs1(v,x);
		Size[x] += Size[v];
		if(max_son<Size[v])
			son[x] = v,max_son = Size[v];
	}
	return;
}

void dfs2(int u,int beg)
{
	dnf[u] = ++inx;
	top[u] = beg;
	if(e_k[u].size() == 0)
		return;
	dfs2(son[u],beg);
	for(auto v:e_k[u])
		{
			if(son[u] == v)
				continue;
			dfs2(v,v);
		}
}
int lca(int a,int b){
	if(dnf[a] < dnf[b])
		swap(a,b);
	if(top[a] == top[b])
	{
		return b;
	}
	return lca(fa[top[a]],b);
}
void init_lca()
{
	for(int i=1;i<=cnt;i++)
	{
		if(pre[i]==i)
		{
			dfs1(i,i);
			dfs2(i,i);
		}
	}
}
void kruskal()
{
	sort(e.begin(),e.end());
	init();
	
	for(auto e1 : e)
	{
		
		if(islink(e1.fr,e1.to))
			continue;
		e_k[++cnt].push_back(find_p(e1.to));
		e_k[cnt].push_back(find_p(e1.fr));
		w[cnt] = e1.v;
		pre[cnt] = cnt;
		add(cnt,find_p(e1.to));
		add(cnt,find_p(e1.fr));
		if(cnt == 2*n-1)
			break;
	}
}
void solve(int a,int b){
	if(!islink(a,b))
	{
		cout<<"impossible\n";
		return;
	}
	cout<<w[lca(a,b)]<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	cnt = n;
	for(int i=1;i<=m;i++)
	{	
		int a,b,l;
		cin>>a>>b>>l;
		e.push_back(edge{a,b,l});
	}
	kruskal();
	init_lca();
	int q;
	cin>>q;
	while(q--)
	{
		int a,b;
		cin>>a>>b;
		solve(a,b);
	}
	return 0;
}
/*
4 5
1 2 5
1 3 2
2 3 11
2 4 6
3 4 4
3
2 3
1 4
1 2

*/
