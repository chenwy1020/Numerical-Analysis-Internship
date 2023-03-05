#include<stdio.h>
void main()
{
	int a,b,i,j,sum=0;
	scanf("%d %d",&a,&b);
	i=a;j=b;
	if(a>b){i=b;j=a;}
	for(;i<=j;i++) sum += i;
	printf("ÇóºÍÎª %d ",sum);
	
	
	
}
 
