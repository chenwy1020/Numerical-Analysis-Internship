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
	printf("����һ�� %d λ����������\n",sizeof(j));
	return 0;
}
