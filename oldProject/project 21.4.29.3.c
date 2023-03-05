#include<stdio.h>
int main()
{
	int i,j,n;
	for(i=1;i<=4;i++)
	{
		for(j=1,n=1;j<=5;j++,n++)
		{
			
			printf("%d\t",i*j);
			if(n%5==0)printf("\n");

		}
	}
	printf("\n");
	return 0;
}
