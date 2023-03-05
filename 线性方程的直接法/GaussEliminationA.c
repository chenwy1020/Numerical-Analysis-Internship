#include<stdio.h>
#include<math.h>

// Gauss 直接消元法 
void GaussianEliminationA(double A[], double b[], int n)
{
	int i, j, k;
	double l;
	
	// 按行消元 
	for(i=0; i<n-1; i++){
		for(k=i+1; k<n; k++){
			// 对矩阵 A 变换 
			l=A[k*n+i]/A[i*n+i];  A[k*n+i]=0;	
			for( j=i+1; j<n; j++){
				A[k*n+j]=A[k*n+j]-l*A[i*n+j];
			}
			
			// 对右端向量 b 变换 
			b[k]=b[k]-l*b[i];
		}
	}
}

//U为上三角矩阵，求解 Ux=y 
void UpTriSys(double U[],double x[],double y[],int n)
{
	int i,j,m;
	double p[n];
	for(j=0;j<n;j++)
		p[j]=y[j];
	for(j=n;j>=1;j--)
	{
		m=(j-1)*(n+1);
		x[j-1]=p[j-1]/U[m];
		for(i=j-1;i>=1;i--)
			p[i-1]=p[i-1]-U[(i-1)*n+j-1]*x[j-1];
	}
}

//矩阵输出
void MatPrintf(double Q[],int m,int n) 
{
	int i;
	for(i=1;i<=m*n;i++)
	{
		printf("%lf ",Q[i-1]);
		if(i%n==0) printf("\n");
	}
}

int main(){
	// 测试数据
	//int n=5;
	//int i, j;
	//double A[25]={-1,0,8,27,64,3,0,12,27,48,-3,0,6,9,12,1,1,1,1,1,156.25,64,4,0.25,0}; 
	//double b[5]={0,0,0,0,4},x[n];
	int n=2;
	int i,j;
	double A[4]={0.75,15.0/32,15.0/32,21.0/64};
	double b[2]={7.0/12,31.0/80},x[2];
	
	// Gauss 消元
	GaussianEliminationA(A, b, n);
	printf("A =\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%lf ", A[i*n+j]);
		}
		printf("\n");
	} 
	
	// 输出 b 
	printf("b =\n");
	for(i=0; i<n; i++){ printf("%lf\n", b[i]); }
	
	UpTriSys(A,x,b,n);
	
	printf("x =\n");
	MatPrintf(x,n,1);
	
	return 0;
}
