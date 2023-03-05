#include<stdio.h>
#include<math.h>
//矩阵继承
void MatCon(double Q[],double z[],int n)
{
	int i;
	for(i=0;i<n*n;i++)
		z[i]=Q[i];
} 
 
// 获取下三角部分
void MatrixLower(double A[], double L[], int n)
{
	int i, j;
	
	for(i=0; i<n; i++){	L[i*n+i]=A[i*n+i];}
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
	
	for(i=0; i<n; i++){	U[i*n+i]=1;}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			U[j*n+i]=0;
			U[i*n+j]=A[i*n+j];
		}
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

//方阵转置 
void MatT(double Q[],int n)
{
	double t;
	int p,q,i,j;
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
		{
			p=(i-1)*n+j-1;
			q=(j-1)*n+i-1;
			t=Q[p];
			Q[p]=Q[q];
			Q[q]=t;
		}
}

//Cholesky分解,并将信息保存在A中 
void Cholesky(double A[],int n)
{
	int i,k,j;
	
	//计算L并将相应元素储存在对应的位置
	for(j=1;j<=n;j++)
	{
		//对角线元素 
		for(k=1;k<=j-1;k++)
			A[(j-1)*(n+1)]-=A[(j-1)*n+k-1]*A[(j-1)*n+k-1];
		A[(j-1)*(n+1)]=sqrt(A[(j-1)*(n+1)]);
		
		//第 j列元素
		for(i=j+1;i<=n;i++)
		{
			for(k=1;k<=j-1;k++)
				A[(i-1)*n+j-1]-=A[(i-1)*n+k-1]*A[(j-1)*n+k-1];
			A[(i-1)*n+j-1]=A[(i-1)*n+j-1]/A[(j-1)*n+j-1];
		}
	}		
}

int main(){
	// 相关函数声明 
	void MatrixUpper(double A[], double U[], int n);
	void MatT(double Q[],int n); 
	void MatMul(double A[],double B[],double y[],int m,int n,int p);
	void Cholesky(double A[],int n);
	void MatPrintf(double Q[],int m,int n);
	void MatCon(double Q[],double z[],int n); 
	
	
	int i, j, n=3;
	
	// 测试数据
	double A[9]={4,2,2,2,5,3,2,3,6};
	
	// 输出 A
	printf("A =\n");
	MatPrintf(A,n,n);
	
	// Cholesky分解
	Cholesky(A,n);
	
	// 输出L
	double L[9];
	MatrixLower(A, L, n);
	printf("L =\n");
	MatPrintf(L,n,n);	
	
	// 输出L' 
	double U[9];
	MatCon(L,U,n);
	MatT(U,n);
	printf("U =\n");
	MatPrintf(U,n,n);	 
	
	// 输出 L*U
	double LU[9];
	MatMul(L,U,LU,n,n,n);
	printf("\nL*L' =\n");
	MatPrintf(LU,n,n); 
	
	return 0;
}
