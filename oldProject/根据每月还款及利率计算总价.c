#include<stdio.h>
int main()
{
	float s,S=0,c,p=1;
	int i,n;
	scanf("%f%f%d",&s,&c,&n); 
	for(i=1;i<=n;i++)
	{
		p=p*(1+c/12.0);
		S=S+s*p;
	}
	printf("%.2f",S);
 } 
