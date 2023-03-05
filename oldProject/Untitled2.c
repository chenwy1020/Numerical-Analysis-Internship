#include<stdio.h>
#include<math.h>
double *A(double a[],double b[],int n)
{
	int i,k;
	double *y;
	y[0]=0;
	for(i=1;i<=n;i++)
		y[0]+=a[i-1]*b[i-1];
	return(y);
}
int main()
{
	double a[3]={1,2,3},b[3]={1,2,3},*c;
	double *A(double a[],double b[],int n);
	c=A(a,b,3);
	printf("%lf",c[0]);
	
}
