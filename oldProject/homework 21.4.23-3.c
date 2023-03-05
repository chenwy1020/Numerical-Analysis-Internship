#include<stdio.h>
int main()
{
	int num,i,j;
	scanf("%d",&num);
	j=num;
	do
	{
		i=num%10;
		printf("%d\n",i);
		num/=10;
	}while(num!=0);
	printf("这是一个 %d 位数的正整数\n",sizeof(j));
	return 0;
}
