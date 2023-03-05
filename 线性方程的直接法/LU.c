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

//Doolittle分解,并将信息保存在A中 
void DoolittleLU(double A[],int n)
{
	int i,k,j;
	for(i=1;i<=n;i++)
	{
		//计算U并将元素储存在A对应的位置
		for(k=i;k<=n;k++)
			for(j=1;j<=i-1;j++)
				A[(i-1)*n+k-1]-=A[(i-1)*n+j-1]*A[(j-1)*n+k-1];
		//计算L并将相应元素储存在对应的位置
		for(k=i+1;k<=n;k++)
		{
			for(j=1;j<=i-1;j++)
				A[(k-1)*n+i-1]-=A[(k-1)*n+j-1]*A[(j-1)*n+i-1];
			A[(k-1)*n+i-1]=A[(k-1)*n+i-1]/A[(i-1)*n+i-1];
		}
	}		
}


//Crout分解 
void CroutLU(double A[],int n)
{
	int i,k,j;
	for(i=1;i<=n;i++)
	{
		//计算U并将元素储存在A对应的位置
		for(k=i;k<=n;k++)
			for(j=1;j<=i-1;j++)
				A[(k-1)*n+i-1]-=A[(k-1)*n+j-1]*A[(j-1)*n+i-1];
		//计算L并将相应元素储存在对应的位置
		for(k=i+1;k<=n;k++)
		{
			for(j=1;j<=i-1;j++)
				A[(i-1)*n+k-1]-=A[(j-1)*n+k-1]*A[(i-1)*n+j-1];
			A[(i-1)*n+k-1]=A[(i-1)*n+k-1]/A[(i-1)*n+i-1];
		}
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

//矩阵输出
void MatPrintf(double Q[],int n) 
{
	int i;
	for(i=1;i<=n*n;i++)
	{
		printf("%lf ",Q[i-1]);
		if(i%n==0) printf("\n");
	}
}

//方阵乘法
void MatMul(double A[],double B[],double y[],int n)
{
	int i,j,k;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			y[(i-1)*n+j-1]=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			for(k=1;k<=n;k++)
				y[(i-1)*n+j-1]+=B[(k-1)*n+j-1]*A[(i-1)*n+k-1];
}

int main()
{
	void MatMul(double A[],double B[],double y[],int n);
	void MatPrintf(double Q[],int n);
	void DoolittleLU(double A[],int n);
	void CroutLU(double A[],int n);
	void UpTriSys(double U[],double x[],double y[],int n);
	void DwTriSys(double L[],double x[],double y[],int n);
	void LUSolver(double L[],double U[],double x[],double b[],int n);
	
	int n=3,i,j;
	double A[9]={2,4,-2,1,-1,5,4,1,-2},y[3]={6,0,2},Q[9],x[9],z[9];
	//double L[9]={1,0,0,0,1,0,0,0,1},U[9]={0};
	double L[9]={0},U[9]={1,0,0,0,1,0,0,0,1};
	
	printf("A =\n");
	MatPrintf(A,n);
	
	//DoolittleLU(A,n);
	CroutLU(A,n);
	if(L[0]==1)
	{
		for(i=1;i<=n;i++)
			for(j=1;j<=i-1;j++)
				L[(i-1)*n+j-1]=A[(i-1)*n+j-1];
		for(i=1;i<=n;i++)
			for(j=i;j<=n;j++)
				U[(i-1)*n+j-1]=A[(i-1)*n+j-1];
	}
	else
	{
		for(i=1;i<=n;i++)
			for(j=1;j<=i;j++)
				L[(i-1)*n+j-1]=A[(i-1)*n+j-1];
		for(i=1;i<=n;i++)
			for(j=i+1;j<=n;j++)
				U[(i-1)*n+j-1]=A[(i-1)*n+j-1];
	}
	
	printf("L =\n");
	MatPrintf(L,n);
	
	printf("U =\n");
	MatPrintf(U,n);
	
	MatMul(L,U,x,n);
	printf("\nL*U =\n");	
	MatPrintf(x,n);
	
}


























