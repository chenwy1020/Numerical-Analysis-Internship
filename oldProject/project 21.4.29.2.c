#include<stdio.h>
int main()
{
	int n,i;
	for(i=0,n=100;n<=200;n++)
	{
		if(n%3==0)continue;
		i++;
		printf("%d\t",n);
		if(i%5==0)printf("\n");
	}
	printf("\n");
	return 0;
}
