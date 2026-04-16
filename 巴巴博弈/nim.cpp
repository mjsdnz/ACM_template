#include<iostream>
#include<cstdio>
#include<vector> 
#include<cstring>
#define int long long
using namespace std;
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
	
		int n;
		cin>>n;
		int x = 0, a;
		for(int i=1;i<=n;i++)
			cin>>a,x^=a;
		if(!x)
		cout<<"No\n";
		else
		cout<<"Yes\n";
		
	}
	return 0;
 } 
