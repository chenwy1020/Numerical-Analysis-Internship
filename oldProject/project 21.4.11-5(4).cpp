#include<stdio.h>
int main()
{
	int x,y,i;
	scanf("%d",x);
	do
	{
		y=x%10;
		printf("%d\t",y);
		x=x/10;
	}while(x=0);
	printf("\n")
}
