#include<stdio.h>
int main()
{
	int i,j,m,n;
	int com_num(int x,int y);
	scanf("%d",&n);
	printf("1\n");
	for(i=1;i<=n-1;i++)
	{
		for(j=0;j<=i;j++)
		{
			m=com_num(i,j);
			printf("%d\t",m);
		}
		printf("\n");
	}
	return 0;
}
int com_num(int x,int y)
{
	int z,m1=1,m2=1,m3=1,i;
	
	for(i=1;i<=x;i++)  m1=m1*i;
	for(i=1;i<=y;i++)  m2=m2*i;
	for(i=1;i<=x-y;i++)m3=m3*i;
	
	z=m1/(m2*m3);
	return(z);
}
