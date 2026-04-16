#include<iostream>
using namespace std;
long long a[100001],p[100001];long long N = 1,ans = 0;
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0) 
	{
			x = 1,y = 0;
		return a;
	}
	else
	{
		int gcd = exgcd(b,a%b,x,y);
		int xx = y;
		y = x-(a/b)*y;
		x = xx;
		return gcd; 
	} 
}
int inv(int a,int p)
{
	int x,y;
	int gcd = exgcd(a,p,x,y);
	if(gcd != 1)
		return -1;
	return (x%p+p)%p;
} 
int main()
{
	
    int n,t;
//	int a1=1,a2=2,a3=4,a4=6,p1=3,p2=5,p3=7,p4=13;
    cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>p[i];
	
	for(int i=1;i<=n;i++)
		N *= p[i];
	for(int i=1;i<=n;i++)
	{
		ans += a[i] * (N/p[i]) * inv((N/p[i]),p[i]);
		ans %= N;
	}
    cout<<(t-1)*N+(ans);
	return 0;
}
/*
4 1
1 2 4 6
3 5 7 13

3 1
2 3 2
3 5 7
*/
