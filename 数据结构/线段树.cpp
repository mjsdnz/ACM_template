#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int MAX = 10000001;
int a[MAX];
int mod;
struct node{
	int l,r,sum,lz1,lz2;
}tr[4*MAX];
void pushup(int x)
{
	tr[x].sum = (tr[x<<1].sum + tr[x<<1|1].sum) % mod;
}
void pushdown(int x)
{
	int lz1 = tr[x].lz1 , lz2 = tr[x].lz2;
	auto& ll = tr[x<<1],& rr = tr[x<<1|1];
	ll.lz2 *= lz2;
	ll.lz1 *= lz2;
	ll.sum *= lz2;
	rr.lz2 *= lz2;
	rr.lz1 *= lz2;
	rr.sum *= lz2;
	rr.lz2 %= mod;
	rr.lz1 %= mod;
	rr.sum %= mod;
	ll.lz2 %= mod;	
	ll.sum %= mod;	
	ll.lz1 %= mod;
	ll.lz1 += lz1;
	rr.lz1 += lz1;
	ll.sum += (ll.r - ll.l + 1) * lz1;
	ll.sum %= mod;
	rr.sum += (rr.r - rr.l + 1) * lz1;
	rr.sum %= mod;
	tr[x].lz1 = 0;
	tr[x].lz2 = 1;
	return;
}
void build(int l,int r,int x)
{
	if(l==r)
		tr[x]={l,r,a[l],0,1};
	else
	{
		int mid = (l + r) >> 1;
		tr[x] = {l,r,0,0,1};
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		pushup(x);
	}
}
void add(int l,int r,int x,int t)
{
	tr[x].sum %= mod;
	if(tr[x].l >= l and tr[x].r <=  r)
	{
		tr[x].sum += (tr[x].r - tr[x].l +1) * t;
		tr[x].sum %= mod;
		tr[x].lz1 += t;
	
		return; 
	}
	else
	{
		tr[x].sum %= mod;
		pushdown(x);
		int mid = (tr[x].l +tr[x].r) >> 1;
		if(mid >= l)
			add(l,r,x<<1,t);
		if(mid < r)
			add(l,r,x<<1|1,t);
		pushup(x); 
	}
}
void mul(int l,int r,int x,int t)
{
	tr[x].sum %= mod;
	if(tr[x].l >= l and tr[x].r <=  r)
	{
		tr[x].sum *=  t;
		tr[x].sum %= mod;
		tr[x].lz1 *= t;
		tr[x].lz1 %= mod;
		tr[x].lz2 *= t;
		tr[x].lz2 %= mod;
		return; 
	}
	else
	{
		pushdown(x);
		int mid = (tr[x].l +tr[x].r) >> 1;
		if(mid >= l)
			mul(l,r,x<<1,t);
		if(mid < r)
			mul(l,r,x<<1|1,t);
		pushup(x); 
	}
}
int query(int l,int r,int x)
{
	tr[x].sum %= mod;
	if(tr[x].l >= l and tr[x].r <= r)
	{
		return tr[x].sum%mod;
	}
	else
	{
		pushdown(x);
		int mid = (tr[x].l +tr[x].r) / 2,ret = 0;
		if(mid >= l)
			ret += query(l,r,x<<1)% mod;
		if(mid < r)
			ret += query(l,r,x<<1|1)% mod;
		return ret % mod;
	}
}
signed main()
{
	int n,q;
	//freopen("r.in","r",stdin);
	cin>>n>>q>>mod;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	build(1,n,1);
	while(q--)
	{
		int op;
		cin>>op;
		if(op == 1)
		{
			int l,r,t;
			cin>>l>>r>>t;
			add(l,r,1,t);
		}
		if(op == 2)
		{
			int l,r,t;
			cin>>l>>r>>t;
			mul(l,r,1,t);
		}
		if(op == 3)
		{
			int l,r;
			cin>>l>>r;
			cout<<query(l,r,1)<<endl;
		}
	}
	return 0;
 } 
 /*
5 5 37
1 5 4 2 3
2 1 4 1
3 2 5
1 2 4 2
2 3 5 5
3 1 4
*/
