#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100001];
int mod;
const int maxn=100001;
class node{
public:
	int sum,lz1,lz2,ll,rr,size;
	node *lc,*rc;
public:
	node():sum(0),size(0),ll(0),rr(0),lz1(0),lz2(1),lc(0),rc(0){}
	node(node *l,node *r,int s,int z1,int z2,int L,int R):sum(s),size(R-L+1),ll(L),rr(R),lz1(z1),lz2(z2),lc(l),rc(r){};
	void push_up();
	void push_down();
};
class xds{
public:
	int n;
	int *init;
	node tree[100001<<1];
	void build(int u,int l,int r);
	node *creat(int n,int a[]);
	void push_up(int u);
	void push_down(int u);
	void add(node *p,int l,int r,int x);
	void mul(node *p,int l,int r,int x);
	int query(node *p,int l,int r);
	
};
void node:: push_down()
{
	lc->sum = (lc->sum * lz2) % mod;
	lc->lz1 = (lc->lz1 * lz2) % mod;
	lc->lz2 = (lc->lz2 * lz2) % mod;
	rc->sum = (rc->sum * lz2) % mod;
	rc->lz1 = (rc->lz1 * lz2) % mod;
	rc->lz2 = (rc->lz2 * lz2) % mod;
	lc->lz1 = (lc->lz1 + lz1) % mod;
	rc->lz1 = (rc->lz1 + lz1) % mod;
	lc->sum = (lc->sum + lz1 * lc->size) % mod;
	rc->sum = (rc->sum + lz1 * rc->size) % mod;
	lz1 = 0;
	lz2 = 1;
	return;
}
void node::push_up()
{
	sum = (lc->sum + rc->sum) % mod;
	return;
}

node *xds::creat(int n,int a[])
{
	init = a;   
	build(1,1,n);
	return &tree[1];
}
void xds::build(int u,int l,int r)
{
	if(l==r)
	{
		tree[u].sum = init[l] % mod;
		tree[u].ll = tree[u].rr = l;
		tree[u].size = 1;
		tree[u].lz2 = 1;
		tree[u].lc = tree[u].rc = nullptr;
		return;
	}
	int mid = (l+r)/2;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	tree[u] = node(&tree[u<<1],&tree[u<<1|1],0,0,1,l,r);
	tree[u].push_up();
	return;
}
void xds::add(node *p,int l,int r,int x)
{
	if(p->rr<l or p->ll >r)
		return;
	if(p->ll >= l and p->rr <= r)
	{
		p->sum = (p->sum + p->size * x) % mod;
		p->lz1 = (p->lz1 + x) % mod;
		return;
	}
	p->push_down();
	add(p->lc,l,r,x);
	add(p->rc,l,r,x);
	p->push_up();
	return;
}
void xds::mul(node *p,int l,int r,int x)
{
	if(p->rr<l or p->ll >r)
		return;
	if(p->ll >= l and p->rr <= r)
	{
		p->sum = (p->sum * x) % mod;
		p->lz1 = (p->lz1 * x) % mod;
		p->lz2 = (p->lz2 * x) % mod;
		return;
	}
	p->push_down();
	mul(p->lc,l,r,x);
	mul(p->rc,l,r,x);
	p->push_up();
	return;

}
int xds::query(node *p,int l,int r)
{
	if(p->ll>=l and p->rr<=r)
	{
		return p->sum;
	}
	if(p->ll>r or p->rr<l)
		return 0;
	p->push_down();
	int ans = 0;
	ans = (ans + query(p->lc,l,r)) % mod;
	ans = (ans + query(p->rc,l,r)) % mod;
	return ans;
}
xds tr;
node *root;
int son[maxn];
int fa[maxn];
int top[maxn];
int num[maxn];
int ord[maxn];
int dnf[maxn];
int dnf_r[maxn];
vector<int> e[maxn];
int cnt;
int R;
void dfs1(int u)
{
	ord[u] = ++cnt;
	num[u]++;
	if(e[u].size() == 1 and u!=R)
		return;
	int max_num=0;
	for(auto v:e[u])
	{
		if(ord[v])
			continue;
		fa[v] = u;
		dfs1(v);
		if(max_num<num[v])
		son[u] = v,max_num = num[v];
		num[u] += num[v];
	}
	return;
}
int cnt2 = 0;
int b[1000001];
void dfs2(int u,int pre,int beg)
{
	top[u] = beg;
	dnf[u] = ++cnt2;
	dnf_r[cnt2] = u;
	b[cnt2] = a[u];
	if(e[u].size() == 1 and u != R)
		return;
	dfs2(son[u],u,beg);
	for(auto v:e[u])
	{
		if(v == pre or v == son[u])
			continue;
		dfs2(v,u,v);
	}
	return;
}
void add_sontree(int u,int x)
{
	tr.add(root,dnf[u],dnf[u]+num[u]-1,x);
	return;
}
void mul_sontree(int u,int x)
{
	tr.mul(root,dnf[u],dnf[u]+num[u]-1,x);
	return;
}
void add_line(int x,int y,int v)
{
	if(top[x]==top[y])
		tr.add(root,min(dnf[x],dnf[y]),max(dnf[x],dnf[y]),v);
	if(dnf[top[x]]<dnf[top[y]])
		add_line(fa[top[y]],x,v) , tr.add(root,dnf[top[y]],dnf[y],v);
	if(dnf[top[x]]>dnf[top[y]])
		add_line(fa[top[x]],y,v) , tr.add(root,dnf[top[x]],dnf[x],v);
	return;
}
int query_line(int x,int y)
{
	if(top[x]==top[y])
		return tr.query(root,min(dnf[x],dnf[y]),max(dnf[x],dnf[y]));
	if(dnf[top[x]]<dnf[top[y]])
		return (query_line(fa[top[y]],x) + tr.query(root,dnf[top[y]],dnf[y]))%mod;
	if(dnf[top[x]]>dnf[top[y]])
		return (query_line(fa[top[x]],y) + tr.query(root,dnf[top[x]],dnf[x]))%mod;
	return 0;
}
int query_sontree(int x)
{
	return tr.query(root,dnf[x],dnf[x] + num[x]-1);
}
signed main()
{
	int n,q;
	cin>>n>>q>>R>>mod;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(R);
	dfs2(R,R,R);
	root = tr.creat(n,b);
//	cout<<"test:";
//	for(int i=1;i<=n;i++)
//		cout<<top[i]<<" ";
//	cout<<endl;
	while(q--)
	{
		int op;
		cin>>op;
		if(op == 1)
		{
			int x,y,z;
			cin>>x>>y>>z;
			add_line(x,y,z);
		}
		if(op == 2)
		{
			int x,y,z;
			cin>>x>>y;
			cout<<query_line(x,y)<<endl;
		}
		if(op == 3)
		{
			int x,y;
			cin>>x>>y;
			add_sontree(x,y);
		}
		if(op == 4)
		{
			int x;
			cin>>x;
			cout<<query_sontree(x)<<endl;
				}
	}
	return 0;
}
/*
6 5 2 24
1 2 3 4 5 6
1 2
3 6
1 5
3 1
4 1
3 4 2
3 2 2
4 5
1 5 1 3
2 1 3
*/
