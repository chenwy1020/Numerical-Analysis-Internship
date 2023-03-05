#include<stdio.h>
int main()
{
	int i,j,n;
	for(i=1;i<=5;i++)
	{
		for(j=1;j<=i;j++) printf(" ");
		for(n=1;n<=10;n++) printf("*");
		printf("\n");
	}
}
