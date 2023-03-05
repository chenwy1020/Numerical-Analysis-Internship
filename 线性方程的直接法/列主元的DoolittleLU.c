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

// ��¼ PA=LU �� P,��ʹ nA ��¼��A�� 
void PA(double A[],double P[],int n)
{
	int i, j, k,r;
	double l,t,B[9];
	for(i=0;i<n*n;i++)B[i]=A[i];
	// ������Ԫ 
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
			for(j=1;j<=n;j++)
			{
				t=P[(i-1)*n+j-1];
				P[(i-1)*n+j-1]=P[(r-1)*n+j-1];
				P[(r-1)*n+j-1]=t;
				
				t=B[(i-1)*n+j-1];
				B[(i-1)*n+j-1]=B[(r-1)*n+j-1];
				B[(r-1)*n+j-1]=t;	
			}
		}	
		// �Ծ��� A �任 
		for(k=i+1; k<=n; k++)
		{
			l=-A[(k-1)*n+i-1]/A[(i-1)*n+i-1];  
			A[(k-1)*n+i-1]=0;	
			for( j=i+1; j<=n; j++)
				A[(k-1)*n+j-1]+=l*A[(i-1)*n+j-1];
		}
	}
	
	for(i=0;i<n*n;i++)A[i]=B[i];
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
	void DoolittleLU(double A[],int n);
	void PA(double A[],double P[],int n);
	
	int n=3,i,j;
	double A[9]={2,4,-2,1,-1,5,4,1,-2},b[3]={6,0,2},B[9]={2,4,-2,1,-1,5,4,1,-2},x[3],y[9];
	double L[9]={1,0,0,0,1,0,0,0,1},U[9]={0};
	double P[9]={1,0,0,0,1,0,0,0,1};
	
	printf("A =\n");	
	MatPrintf(A,n,n);
	
	PA(A,P,n);
	DoolittleLU(A,n);
	for(i=1;i<=n;i++)
		for(j=1;j<=i-1;j++)
			L[(i-1)*n+j-1]=A[(i-1)*n+j-1];
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			U[(i-1)*n+j-1]=A[(i-1)*n+j-1];
			
	printf("nA =\n");
	MatPrintf(A,n,n);
	printf("L =\n");
	MatPrintf(L,n,n);
	
	printf("U =\n");
	MatPrintf(U,n,n);
	
	printf("P =\n");
	MatPrintf(P,n,n);
		
	MatMul(L,U,y,n,n,n);
	printf("\nL*U =\n");
	MatPrintf(y,n,n);
	
	MatMul(P,B,y,n,n,n);
	printf("\nP*A =\n");	
	MatPrintf(y,n,n);

	
}
