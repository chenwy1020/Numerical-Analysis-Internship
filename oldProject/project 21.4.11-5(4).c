#include<stdio.h>
int main()
{
	int x,y;
	scanf("%d",&x);
	do
	{
		y=x%10;
		printf("%d",y);
		x=x/10;
	}while(x!=0);
	printf("\n");
	printf("½áÊø");
}
