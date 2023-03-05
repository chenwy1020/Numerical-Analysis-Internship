#include<stdio.h>
#include<math.h>

double MatNorm1(double A[], int m,int n)
{
	int i,j;
	double v=0,a[n];
	for(j=0;j<n;j++)
		a[j]=0;	
	for(j=0;j<n;j++)
		for(i=j;i<n*m;i+=n)
			a[j]+=fabs(A[i]);
	for(j=0;j<n;j++)
		if(v<a[j])
			v=a[j];
	
	return(v);
}

double MatNorminf(double A[], int m,int n)
{
	int i=0,j;
	double v=0,a[m];
	for(j=0;j<m;j++)
		a[j]=0;	
	for(j=0;j<m;j++)
		for( ;i<(j+1)*n;i++)
			a[j]+=fabs(A[i]);
	for(j=0;j<m;j++)
		if(v<a[j])
			v=a[j];
	
	return(v);
}

double MatNormF(double A[], int m,int n)
{
	int i;
	double v=0;
	for(i=0;i<n*m;i++)
		v+=A[i]*A[i];
	
	return(sqrt(v));
}

int main()
{
	double MatNorm1(double A[], int m,int n);
	double MatNorminf(double A[], int m,int n);
	double MatNormF(double A[], int m,int n);
	
	int mA=2,nA=3,mB=3,nB=2;
	double A[6]={1,3,-2,-2,0,5};
	double B[6]={4,3,1,-2,0,8};
	
	printf("Norm1_A = %lf\n",MatNorm1(A,mA,nA));
	printf("Norminf_A = %lf\n",MatNorminf(A,mA,nA));
	printf("NormF_A = %lf\n",MatNormF(A,mA,nA));
	printf("Norm1_B = %lf\n",MatNorm1(B,mB,nB));
	printf("Norminf_B = %lf\n",MatNorminf(B,mB,nB));
	printf("NormF_B = %lf\n",MatNormF(B,mB,nB));
	
	return 0;
}
	



