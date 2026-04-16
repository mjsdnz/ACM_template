#include<iostream>
#define int long long
using namespace std;
int a1[5000001];
int exgcd(int a,int b,int &x,int &y,int d)
{
	if(b==0) 
	{
		if(a % d == 0)
			x = d / a,y = 0;
		return d;
	}
	else
	{
		int gcd = exgcd(b,a%b,x,y ,d);
		int xx = y;
		y = x-(a/b)*y;
		x = xx;
		return gcd; 
	} 
}
int inv(int a,int p)
{
	int x,y;
	int gcd = exgcd(a,-p,x,y,1);
	if(gcd != 1)
	return -1;
	return (x%p+p)%p;
}
signed main()
{
	int n,p,k;
	ios::sync_with_stdio(0);
	cin.tie(0); 
	cin>>n>>p;
	return 0;
}
