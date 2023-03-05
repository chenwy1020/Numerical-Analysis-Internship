#include<stdio.h>
int main()
{
	
	int n;
	for(n=100;n<=200;n++)
	{
		if(n%3==0) continue;
		printf("\t%d",n);
	}
	
	return 0;
	
}
