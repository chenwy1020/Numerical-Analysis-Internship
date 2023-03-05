#include<stdio.h>
int main()
{
	int m=1;
	while(m==1)
	{
	
		int i=3,n,f1=1,f2=1,f,m;
	
		printf("请输入n的值：");
		scanf("%d",&n);
		if(n>=3)
		{
			for(f=2;i<=n;i++)
			{
				f=f1+f2;
				f1=f2;
				f2=f;
		
			}	
			printf("result = %d\n",f);
		}
		else
	
			printf("result = 1\n");
		scanf("%d",&m);
		printf("m 的值是 %d\n ",m);
		
	}
}
