#include<stdio.h>
int main()
{
	int x,y=0,i,n,sum=0;
	scanf("%d %d",&x,&n);
	for(i=1;i<=n;i++) 
	{
		y=y*10+2;
		sum=sum+y;
	}
	printf("result = %d",sum);
}
