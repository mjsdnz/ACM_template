int read()
{
	int a=0;
	char c;
	while(c=getchar())
		if(c>='0' and c<='9')
			break;
	while(c>='0' and c<='9')
	{
		a *= 10;
		a += (c-'0'); 
		c = getchar();
	}
	return a;
}
