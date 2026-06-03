#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000001];
int mod;
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
	node tree[1000001<<1];
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
signed main()
{
	int n,q;
	cin>>n>>q>>mod;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	root = tr.creat(n,a);
	while(q--)
	{
		int op;
		cin>>op;
		if(op == 1)
		{
			int x,y,z;
			cin>>x>>y>>z;
			tr.mul(root,x,y,z);
		}
		if(op == 2)
		{
			int x,y,z;
			cin>>x>>y>>z;
			tr.add(root,x,y,z);
		}
		if(op == 3)
		{
			int x,y;
			cin>>x>>y;
			cout<<tr.query(root,x,y)<<endl;
		}
		
	}
	return 0;
}
