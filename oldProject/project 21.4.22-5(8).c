#include<stdio.h>
int main()
{
	int i,j;
	printf("     ");
	for(i=1;i<=9;i++)printf("(%d)\t",i);
	printf("\n");
	for(i=1;i<=9;i++)
	{
		printf("(%d)   ",i);
		for(j=1;j<=9;j++)printf("%d\t",i*j);
		printf("\n");
	}	
	
}
