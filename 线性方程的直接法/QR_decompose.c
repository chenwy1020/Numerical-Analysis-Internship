#include<stdio.h>
#include<math.h>
//Given�任 ��Q,R,b����� 
void Given(double A[],double Q[],double y[],int n)
{
	void MatT(double Q[],int n);
	int i,j,k,p,q;
	double c,s,t;
	for(i=1;i<=n*n;i++)
		Q[i-1]=0;
	for(i=1;i<=n;i++)
		Q[(i-1)*(n+1)]=1;
	for(i=1;i<=n;i++) 
	{
		for(j=i+1;j<=n;j++)
		{
			//Step1: ����Givens ����
			p=(i-1)*(n+1);
			q=(j-1)*n+i-1;
			c=A[p]/sqrt(A[p]*A[p]+A[q]*A[q]);
			s=A[q]/sqrt(A[p]*A[p]+A[q]*A[q]);
			A[p]=sqrt(A[p]*A[p]+A[q]*A[q]);
			A[q]=0;
			
			//Step2: �Ե�i, j �е�����Ԫ�ؽ��б任�õ�����R
			for(k=i+1;k<=n;k++)
			{
				p=(i-1)*n+k-1;
				q=(j-1)*n+k-1;
				t=A[p];
				A[p]= c*t+s*A[q];
				A[q]=-s*t+c*A[q];
			}
			//Step3: ���Ҷ����i, j Ԫ�ؽ��б任
			t=y[i-1];
			y[i-1]= c*t+s*y[j-1];
			y[j-1]=-s*t+c*y[j-1];
			
			//Step4: ����������Q �ĵ�i, j ��Ԫ�ؽ��б任
			for(k=1;k<=n;k++)
			{
				p=(i-1)*n+k-1;
				q=(j-1)*n+k-1;
				t=Q[p];
				Q[p]= c*t+s*Q[q];
				Q[q]=-s*t+c*Q[q];
			}	
		}
	}
	//��Q��ת�� 
	MatT(Q,n);	
}

//AΪ�����Ǿ������ Ax=y 
void UpTriSys(double A[],double x[],double y[],int n)
{
	int i,j,m;
	double p[n];
	for(j=0;j<n;j++)
		p[j]=y[j];
	for(j=n;j>=1;j--)
	{
		m=(j-1)*(n+1);
		x[j-1]=p[j-1]/A[m];
		for(i=j-1;i>=1;i--)
			p[i-1]=p[i-1]-A[(i-1)*n+j-1]*x[j-1];
	}
}

//����ת�� 
void MatT(double Q[],int n)
{
	double t;
	int p,q,i,j;
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
		{
			p=(i-1)*n+j-1;
			q=(j-1)*n+i-1;
			t=Q[p];
			Q[p]=Q[q];
			Q[q]=t;
		}
}

//�������
void MatPrintf(double Q[],int n) 
{
	int i;
	for(i=1;i<=n*n;i++)
	{
		printf("%lf ",Q[i-1]);
		if(i%n==0) printf("\n");
	}
}

int main()
{
	void Given(double A[],double Q[],double y[],int n);
	void UpTriSys(double A[],double x[],double y[],int n);
	void MatPrintf(double Q[],int n) ;
	int n=3,i;
	double A[9]={2,4,-2,1,-1,5,4,1,-2},b[3]={6,0,2},x[3],y[3]={6,0,2},Q[9];
	
	Given(A,Q,y,n);
	printf("Q =\n");
	MatPrintf(Q,n);
	printf("R =\n");
	MatPrintf(A,n);
	
	UpTriSys(A,x,y,n);
	for(i=0;i<n;i++)
		printf("x[%d][0] = %lf\n",i,x[i]);
	for(i=0;i<n;i++)
		printf("b[%d][0] = %lf\n",i,b[i]);
}
