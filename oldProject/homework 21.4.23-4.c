#include<stdio.h>
#include<math.h>
int main()
{
//  float i,j,x,precision;
//	scanf("%f",&precision);
//	x=1.5;
//	do
//	{
//	i=2*x*x*x-4*x*x+3*x-6;
//	j=6*x*x-8*x+3;
//	x=x-i/j;
//	
//	}while(fabs(2*x*x*x-4*x*x+3*x-6)>=precision);
//	printf("%f",x);
	int a[3][4];
	a[2][0]=1;
	a[2][1]=2;
	a[2][2]=3;
	int *p;
	p=a[2];
	printf("%d",*++p);
	
}








