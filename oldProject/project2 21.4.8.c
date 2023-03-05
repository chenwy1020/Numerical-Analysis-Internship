#include<stdio.h>
#include<math.h>
#include<conio.h>
void main()
{

	char *str="Demo\nTest";
	puts(str);
	puts("\nString");
	printf("abcdefg");
	
	getchar();
	
	
	char string[128];
	gets(string);
	printf("%s\n",string);
	puts(string);
	
	
	char *pch1="CHINA";
	printf("%3s %7.2s %.2s %-5.3s %%",pch1,pch1,pch1,pch1);
	
	
	int ik=80;
	printf("\nThe percent is %d%%",ik);
	
	

	int max(int x,int y);
	int a,b,i,j;
	scanf("%d %d",&a,&b);	
	i=a;
	j=max(a%i,b%i);
	while(j!=0)
	{
		i-=1;
		j=max(a%i,b%i);	
	}
	printf("a与b的最大公约数是 %d",i);
	
}
int max(int x,int y)
{
	int w;
	if(x>y)w=x;
	else w=y;
	return(w);
}

