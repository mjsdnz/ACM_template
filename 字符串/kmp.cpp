#include<bits/stdc++.h>
using namespace std;
int kmp[100001];
vector<int> kmp_ans;
int KMP(char a[],char b[])
{

	for(int i=2,j=0;i<=strlen(b+1);i++)//i=2 is design to avoid 死循环 i，j均定义为下一个要匹配的位置 
	{
		while(j and b[i]!=b[j+1]) j = kmp[j];
		if(b[i] == b[j+1]) j++;
		kmp[i] = j;
	}
	int l=0;
	for(int i=1,j=0;i<=strlen(a+1);i++)
	{
		
		while(j && b[j+1]!=a[i]) j=kmp[j];
		if(b[j+1] == a[i]) j++;
		if(j == strlen(b+1))
			kmp_ans.push_back(i-j+1);
	}
}
int main()
{

	cin>>a+1>>b+1;
	KMP(a,b);
	return 0;
} 
/*用于找出两份字符串的最大配
其中a为文本串，b为模式串
特别提醒字符串中a[0]b[0]无效即应从从a+1开始输入
ans为匹配成功的文本串首字符位置的集合*/
