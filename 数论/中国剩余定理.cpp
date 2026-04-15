#include<iostream>
  using namespace std;
long long f(int x,int y)
{
	if(y^1) 
      {
		long long a=f(x,(y>>1));
        return a*a;
      }
  else
    return f(x,y/2)*x;
}
int main()
{
  int a1=1,a2=2,a3=4,a4=6,p1=3,p2=5,p3=7,p4=13;
  int N=p1*p2*p3*p4;
  int x = a1*f(N/p1,p1-2)*(N/p1)+a2*f(N/p2,p2-2)*(N/p2)+a3*f(N/p3,p3-2)*(N/p3)+a4*f(N/p4,p4-2)*(N/p4);
  int n;
  cin>>n;
  cout<<(n-1)*N+(x);
	return 0;
}
