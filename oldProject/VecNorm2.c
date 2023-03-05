#include<stdio.h>
#include<math.h>

double VecNorm1(double x[],int n)
{
	int i;
	double v=0;
	for(i=0;i<n;i++)
		v+=fabs(x[i]);

	return(v);
}

double VecNorm2(double x[],int n)
{
	int i;
	double v=0;
	for(i=0;i<n;i++)
		v+=x[i]*x[i];
	
	return(sqrt(v));
}

double VecNormInf(double x[],int n)
{
	int i;
	double v=0;
	for(i=0;i<n;i++)
		if(v<fabs(x[i]))
			v=fabs(x[i]);
	return(v);
}

int main()
{
	double VecNorm1(double x[],int n);
	double VecNorm2(double x[],int n);
	double VecNormInf(double x[],int n);
	
	int nx=3,ny=6;
	double x[3]={1,3,2},y[6]={4,3,1,-2,0,8};

	printf("Norm1x= %lf\n",VecNorm1(x,nx));
	printf("Norm2x= %lf\n",VecNorm2(x,nx));
	printf("Norminfx = %lf\n",VecNormInf(x,nx));
	printf("Norm1y = %lf\n",VecNorm1(y,ny));
	printf("Norm2y = %lf\n",VecNorm2(y,ny));
	printf("Norminfy = %lf\n",VecNormInf(y,ny));
	
	return 0;
}
	
