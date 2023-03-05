#include<stdio.h>

int main()
{
	char c;
	int se=0,sk=0,sn=0,so=0;
	for(;(c=getchar())!='\n';)
	{
		if((c>=65&&c<=90)||(c>=97&&c<=122)) se+=1;
		else if(c==32) sk+=1;
		else if(c>=48&&c<=57) sn+=1;
		else so+=1;	
	}
	printf("%d %d %d %d",se,sk,sn,so);
	return 0;
 } 
