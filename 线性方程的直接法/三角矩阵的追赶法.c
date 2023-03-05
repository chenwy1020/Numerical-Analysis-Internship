 #include<stdio.h>
#include<math.h>

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

//L为下三角矩阵，求解 Lx=y 
void DwTriSys(double L[],double x[],double y[],int n)
{
	int i,j,m;
	double p[n];
	for(j=0;j<n;j++)
		p[j]=y[j];
	for(j=1;j<=n;j++)
	{
		m=(j-1)*(n+1);
		x[j-1]=p[j-1]/L[m];
		for(i=j+1;i<=n;i++)
			p[i-1]=p[i-1]-L[(i-1)*n+j-1]*x[j-1];
	}
}

//求解 LUx=b 
void LUSolver(double L[],double U[],double x[],double b[],int n)
{
	void UpTriSys(double U[],double x[],double y[],int n);
	void DwTriSys(double L[],double x[],double y[],int n);
	double p[n];
	int i;
	DwTriSys(L,x,b,n);
	for(i=0;i<n;i++)
		p[i]=x[i];
	UpTriSys(U,x,p,n);	
}

// 获取单位下三角部分
void MatrixLower(double A[], double L[], int n)
{
	int i, j;
	
	for(i=0; i<n; i++){	L[i*n+i]=1;}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			L[i*n+j]=0;
			L[j*n+i]=A[j*n+i];
		}
	}
}

// 获取上三角部分 
void MatrixUpper(double A[], double U[], int n)
{
	int i, j;
	
	for(i=0; i<n; i++){	U[i*n+i]=A[i*n+i];}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			U[j*n+i]=0;
			U[i*n+j]=A[i*n+j];
		}
	}
}

// Doolittle 算法做 LU 分解,并求解 (A为三角矩阵） 
void Doolittle(double A[],double x[],double b[],int n)
{
	void MatrixLower(double A[], double L[], int n);
	void MatrixUpper(double A[], double U[], int n);
	void LUSolver(double L[],double U[],double x[],double b[],int n);
	
	int i, j, k;
	double L[n*n],U[n*n];
	
	for(i=1; i<n; i++){
		A[i*n+i-1]=A[i*n+i-1]/A[(i-1)*(n+1)];
		A[i*n+i]=A[i*n+i]-A[i*n+i-1]*A[(i-1)*(n+1)];
	}
	MatrixLower(A,L,n);
	MatrixUpper(A,U,n);
	
	LUSolver(L,U,x,b,n);
} 

//矩阵继承
void MatCon(double Q[],double z[],int n)
{
	int i;
	for(i=0;i<n*n;i++)
		z[i]=Q[i];
} 

//矩阵乘法
void MatMul(double A[],double B[],double y[],int m,int n,int p)
{
	int i,j,k;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			y[(i-1)*p+j-1]=0;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			for(k=1;k<=n;k++)
				y[(i-1)*p+j-1]+=A[(i-1)*n+k-1]*B[(k-1)*p+j-1];
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

int main()
{
	void LUSolver(double L[],double U[],double x[],double b[],int n);
	void MatCon(double Q[],double z[],int n);
	void MatMul(double A[],double B[],double y[],int m,int n,int p);
	void MatPrintf(double Q[],int m,int n);
	
	int n=10;
	double A[100]={-4, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					1,-4, 1, 0, 0, 0, 0, 0, 0, 0,
					0, 1,-4, 1, 0, 0, 0, 0, 0, 0,
					0, 0, 1,-4, 1, 0, 0, 0, 0, 0, 
					0, 0, 0, 1,-4, 1, 0, 0, 0, 0,
					0, 0, 0, 0, 1,-4, 1, 0, 0, 0,
					0, 0, 0, 0, 0, 1,-4, 1, 0, 0, 
					0, 0, 0, 0, 0, 0, 1,-4, 1, 0,
					0, 0, 0, 0, 0, 0, 0, 1,-4, 1,
					0, 0, 0, 0, 0, 0, 0, 0, 1,-4};
	double b[10]={-27,-15,-15,-15,-15,-15,-15,-15,-15,-15};	
	double x[n],Q[n*n],z[n];
	MatCon(A,Q,n);
	
	
	printf("A =\n");
	MatPrintf(A,n,n);
	
	printf("b =\n");
	MatPrintf(b,1,n);
	
	Doolittle(A,x,b,n);
	printf("x =\n");
	MatPrintf(x,1,n);
	
	MatMul(Q,x,z,n,n,1);
	printf("A*x =\n");
	MatPrintf(z,1,n);
	
}
