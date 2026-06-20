#include <bits/stdc++.h>
using namespace std;
const double eps=1e-7;
double a[105][105];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++){ 
		int maxx=i;
		for(int j=i+1;j<=n;j++)//找到绝对值最大的系数的所在行
			if(fabs(a[j][i])>fabs(a[maxx][i])) maxx=j;
		for(int j=1;j<=n+1;j++)
			swap(a[i][j],a[maxx][j]);//与第 i 行交换
		if(fabs(a[i][i])<eps){
			//无解或者有无穷多解
			cout<<"No Solution";
			return 0;
		}
		for(int j=n+1;j>=1;j--) a[i][j]=a[i][j]/a[i][i];//把 x_1 的系数转换为 1
		for(int j=1;j<=n;j++){
			if(j!=i){
				//消去其他行的系数
				double tmp=a[j][i]/a[i][i];
				for(int k=1;k<=n+1;k++) a[j][k]-=a[i][k]*tmp;
			}
		}
	}
	for(int i=1;i<=n;i++) printf("%.2lf\n",a[i][n+1]);//输出该线性方程组的解
	return 0;
}
