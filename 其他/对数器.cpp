#include <bits/stdc++.h>
using namespace std;

string mpat("C:/Users/tocar/Desktop/对拍/");		//主路径 注意末尾跟/!!!! linuxpwd查看当前路径

string an("solution"), bn("brute");		//程序名字
int brek = 5;					//几个错误停止 -1不停止
int cmpt = 1;					//编译模式

void exec(const string &cmd, string &res)
{
	char buf[1024];
	FILE *fp = _popen(cmd.c_str(), "r"); //linux下改为popen
	while (fgets(buf, 1024, fp))
		res.append(buf);
	_pclose(fp); 						//linux下改为pclose
}
void wrfile(const string &path, stringstream &ss)
{
	string str;
	FILE *fp = fopen(path.c_str(), "wb");
	while (getline(ss, str))
		fprintf(fp, "%s\r\n", str.c_str());
	fclose(fp);
}
long long d_rand(long long l, long long r)
{
	int k = rand() % 4;
	long long t = rand();
	for (int i = 0; i < k; i++)
		t = t << 16 | rand();
	return l + t % (r - l + 1);
}
double f_rand(double l, double r)
{
	double t = rand() / 32767.0;
	return l + t * (r - l);
}
char c_rand(const string &ch)
{
	return ch[rand() % ch.size()];
}
void sample(stringstream &sout) //样例生成
{
	int a=d_rand(1,5);
	int b=d_rand(2,100);
	sout << a <<" "<<b;
}
int main()
{
	srand(time(NULL));
	rand();
	if (cmpt) //编译功能
	{
		system(("g++ " + mpat + an + ".cpp -o " + mpat + an + ".exe -std=c++11").c_str()); //C++11支持
		system(("g++ " + mpat + bn + ".cpp -o " + mpat + bn + ".exe -std=c++11").c_str());
	}
	string num, aout, bout, spat = mpat + "sample/"; //样例生成子路径
	int cnt = 0, wa = 0;
	while (wa != brek) //几个错误停止
	{
		stringstream ss;
		ss << ++cnt;
		ss >> num;
		aout.clear(), bout.clear(), ss.clear();
		sample(ss);
		wrfile(spat + num + "samp.txt", ss);
		cout << cnt;
		exec(mpat + an + ".exe < " + spat + num + "samp.txt", aout);
		exec(mpat + bn + ".exe < " + spat + num + "samp.txt", bout);
		if (aout == bout)
		{
			remove((spat + num + "samp.txt").c_str());
			remove((spat + num + an + "ans" + an + ".txt").c_str());
			remove((spat + num + bn + "ans" + bn + ".txt").c_str());
		}
		else
		{
			ss.clear();
			ss.str(aout);
			wrfile(spat + num + "ans" + an + ".txt", ss);
			ss.clear();
			ss.str(bout);
			wrfile(spat + num + "ans" + bn + ".txt", ss);
			wa++;
		}
		cout << "\t" << wa << endl;
	}
	
	return 0;
}
