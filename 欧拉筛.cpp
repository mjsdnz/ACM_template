#include<iostream>
#include<cmath>
using namespace std;
int e[1000],top=0,n=999;
bool p[100000];
void evalue()
{
	for(int i=2;i<=n;i++)
	{
		if(!p[i])
			e[++top] = i;
		for(int j=1 ;e[j]*i<=n;j++)
		{
			p[i*e[j]]=true;
			if(i%e[j]==0)
				break;			
		}
	}
}
int main()
{
	evalue();
	return 0;
} 
