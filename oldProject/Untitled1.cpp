#include<stdio.h>
int main()
{
	int s,t,i;
	float b,h=0,H;
	scanf("%d%f%d",&s,&b,&t);
	
	for(i=0;i<=t;i++)
	{
		h=h*(b/12.0+1)+s;
	}
	H=s*t;
	printf("%.2f\n%.2f\n²îÖµÎª:%.2f",h,H,(h-H));
	
 } 
