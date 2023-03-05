#include<stdio.h>
#include<math.h>
//UΪ�����Ǿ������ Ux=y 
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

//LΪ�����Ǿ������ Lx=y 
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

//��� LUx=b 
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

//����˷�
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

//�������
void MatPrintf(double Q[],int m,int n) 
{
	int i;
	for(i=1;i<=m*n;i++)
	{
		printf("%lf ",Q[i-1]);
		if(i%n==0) printf("\n");
	}
}

// Gauss ֱ����Ԫ�� 
void GaussianEliminationA(double A[], double b[], int n)
{
	int i, j, k;
	double l;
	
	// ������Ԫ 
	for(i=0; i<n-1; i++){
		for(k=i+1; k<n; k++){
			// �Ծ��� A �任 
			l=A[k*n+i]/A[i*n+i];  A[k*n+i]=0;	
			for( j=i+1; j<n; j++){
				A[k*n+j]=A[k*n+j]-l*A[i*n+j];
			}
			
			// ���Ҷ����� b �任 
			b[k]=b[k]-l*b[i];
		}
	}
}

// Gauss ����Ԫ��Ԫ�� 
void GaussianA(double A[], double b[], int n)
{
	int i,j,k,r;
	double l,t;
	
	//��Ԫ 
	for(i=1;i<=n-1; i++)
	{
		//����Ԫ
		r=i;
		t=fabs(A[(i-1)*n+i-1]);
		for(k=i+1;k<=n;k++)
		{
			if(t<fabs(A[(k-1)*n+i-1]))
			{
				r=k;
		 		t=fabs(A[(k-1)*n+i-1]);
		 	}
		}
		if(r!=i) 
		{
			for(j=i;j<=n;j++)
			{
		 		t=A[(i-1)*n+j-1];
		 		A[(i-1)*n+j-1]=A[(r-1)*n+j-1];
		 		A[(r-1)*n+j-1]=t;
			}
			t=b[i-1];
			b[i-1]=b[r-1];
			b[r-1]=t;
		}
		
		for(k=i+1; k<=n; k++)
		{
			// �Ծ��� A �任 
			l=-A[(k-1)*n+i-1]/A[(i-1)*n+i-1];  
			A[(k-1)*n+i-1]=0;	
			for( j=i+1; j<=n; j++)
				A[(k-1)*n+j-1]+=l*A[(i-1)*n+j-1];
			
			// ���Ҷ����� b �任 
			b[k-1]+=l*b[i-1];
		}
	}
}


//Doolittle�ֽ�,������Ϣ������A�� 
void DoolittleLU(double A[],int n)
{
	int i,k,j;
	for(i=1;i<=n;i++)
	{
		//����U����Ԫ�ش�����A��Ӧ��λ��
		for(k=i;k<=n;k++)
			for(j=1;j<=i-1;j++)
				A[(i-1)*n+k-1]-=A[(i-1)*n+j-1]*A[(j-1)*n+k-1];
		//����L������ӦԪ�ش����ڶ�Ӧ��λ��
		for(k=i+1;k<=n;k++)
		{
			for(j=1;j<=i-1;j++)
				A[(k-1)*n+i-1]-=A[(k-1)*n+j-1]*A[(j-1)*n+i-1];
			A[(k-1)*n+i-1]=A[(k-1)*n+i-1]/A[(i-1)*n+i-1];
		}
	}		
}

//Crout�ֽ� 
void CroutLU(double A[],int n)
{
	int i,k,j;
	for(i=1;i<=n;i++)
	{
		//����U����Ԫ�ش�����A��Ӧ��λ��
		for(k=i;k<=n;k++)
			for(j=1;j<=i-1;j++)
				A[(k-1)*n+i-1]-=A[(k-1)*n+j-1]*A[(j-1)*n+i-1];
		//����L������ӦԪ�ش����ڶ�Ӧ��λ��
		for(k=i+1;k<=n;k++)
		{
			for(j=1;j<=i-1;j++)
				A[(i-1)*n+k-1]-=A[(j-1)*n+k-1]*A[(i-1)*n+j-1];
			A[(i-1)*n+k-1]=A[(i-1)*n+k-1]/A[(i-1)*n+i-1];
		}
	}	
}


int main()
{
	void MatMul(double A[],double B[],double y[],int m,int n,int p);
	void MatPrintf(double Q[],int m,int n);
	void GaussianA(double A[], double b[], int n);
	void UpTriSys(double U[],double x[],double y[],int n);
	
	/*
	int n=3;
	double A[9]={2,4,-2,1,-1,5,4,1,-2},b[3]={6,0,2},B[9]={2,4,-2,1,-1,5,4,1,-2},x[3],y[3];
	*/
	/*
	int n=5;
	double A[25]={-1,0,8,27,64,3,0,12,27,48,-3,0,6,9,12,1,1,1,1,1,156.25,64,4,0.25,0};
	double B[25]={-1,0,8,27,64,3,0,12,27,48,-3,0,6,9,12,1,1,1,1,1,156.25,64,4,0.25,0};
	double b[5]={0,0,0,0,4},x[n],y[n];
	*/
	int n=4;
	double A[16]={2,1,0,0,0.5,2,0.5,0,0,0.5,2,0.5,0,0,1,2};
	double B[16]={2,1,0,0,0.5,2,0.5,0,0,0.5,2,0.5,0,0,1,2};
	double b[4]={18,24,45,-30},x[n],y[n];
	
	printf("A =\n");
	MatPrintf(A,n,n);
	
	printf("b =\n");
	MatPrintf(b,1,n);
	
	//����Ԫ��ȥ��� nA nb 
	GaussianA(A,b,n);
	printf("nA =\n");
	MatPrintf(A,n,n);
	
	printf("nb =\n");
	MatPrintf(b,1,n);
	
	UpTriSys(A,x,b,n);
	printf("x =\n");
	MatPrintf(x,1,n);
	
	MatMul(A,x,y,n,n,1);
	printf("nA*x =\n");
	MatPrintf(y,n,1);
	
	MatMul(B,x,y,n,n,1);
	printf("\nA*x =\n");	
	MatPrintf(y,n,1);
	
}
