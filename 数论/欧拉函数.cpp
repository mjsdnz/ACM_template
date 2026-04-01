#include<iostream>
#include<cmath>
using namespace std;
int e[1000],f[10001],top=0,n=999;
bool p[100000];
void evalue()
{
	for(int i=2;i<=n;i++)
	{
		if(!p[i])
			e[++top] = i,f[i] = i-1;
		for(int j=1 ;j<=top and e[j]*i<=n;j++)
		{
			p[i*e[j]] = true;
			if(i%e[j]==0)
				{
					f[i*e[j]] = e[j]*f[i];
					break;			
				}
			else
				f[i*e[j]] = f[i] * f[e[j]];

		}
	}
}
int main()
{
	evalue();
	for(int i=1;i<=100;i++)
	{
		cout<<f[i]<<" ";
	}
	return 0;
} 
