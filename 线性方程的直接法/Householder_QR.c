#include<stdio.h>
#include<math.h>

int main(){
	void Householder(double A[],double Q[],double y[],int n);
	void MatMul(double A[],double B[],double y[],int n);
	void MatCon(double Q[],double z[],int n);
	void MatPrintf(double Q[],int n);
	void MatT(double Q[],int n);
	int n=3;
	double A[9]={2,4,-2,1,-1,5,4,1,-2},y[3]={6,0,2},Q[9],x[9],z[9];
	
	printf("A =\n");
	MatPrintf(A,n);
	
	Householder(A,Q,y,n);
	
	printf("\n");
	MatMul(Q,A,x,n);	 
	printf("Q*R =\n");
	MatPrintf(x,n);	
	
	printf("Q =\n");
	MatPrintf(Q,n);
	
	printf("R =\n");
	MatPrintf(A,n);
	
	MatCon(Q,z,n);
	MatT(z,n);
	MatMul(z,Q,x,n);
	x[2]=0;x[6]=0;x[5]=0;x[7]=0;
	printf("Q*Q =\n");
	MatPrintf(x,n);
	getchar();
}

//����̳�
void MatCon(double Q[],double z[],int n){
	int i;
	for(i=0;i<n*n;i++)
		z[i]=Q[i];
} 
 
//����ת�� 
void MatT(double Q[],int n){
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

//�������
void MatPrintf(double Q[],int n) {
	int i;
	for(i=1;i<=n*n;i++)
	{
		printf("%lf ",Q[i-1]);
		if(i%n==0) printf("\n");
	}
}

//����˷�
void MatMul(double A[],double B[],double y[],int n){
	int i,j,k;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			y[(i-1)*n+j-1]=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			for(k=1;k<=n;k++)
				y[(i-1)*n+j-1]+=B[(k-1)*n+j-1]*A[(i-1)*n+k-1];
}

//Householder�任 
void Householder(double A[],double Q[],double y[],int n)
{
	void MatPrintf(double Q[],int n);
	void MatT(double Q[],int n);
	
	int i,j,k,i1,j1;
	double t,t1=0,t2=0,t3=0,v[n];
	double P[n*n];
	//��ʼ�� 
	for(i1=1;i1<=n;i1++)
		for(j1=1;j1<=n;j1++)
		{
			Q[(i1-1)*n+j1-1]=0;
			Q[(i1-1)*(n+1)]=1; 
		}
	for(i=1;i<=n;i++)
		v[i-1]=0;		
		
	for(i=1;i<=n-1;i++)
	{
		
		//���õ�λ��������ɵ�househorder������Ϣ 
		for(i1=1;i1<=n;i1++)
			for(j1=1;j1<=n;j1++)
			{
				P[(i1-1)*n+j1-1]=0;
				P[(i1-1)*(n+1)]=1; 
			}		
		
		//һ.����householder���� 
		
		
		t=0;
		for(k=i;k<=n;k++)
			t+=A[(k-1)*n+i-1]*A[(k-1)*n+i-1];
		t=sqrt(t);
		if(A[(i-1)*(n+1)]<0) t=-t;
		
	
		v[i-1]=A[(i-1)*(n+1)]+t;
		t1=v[i-1]*v[i-1];
		for(k=i+1;k<=n;k++)
		{
			v[k-1]=A[(k-1)*n+i-1];
			t1+=v[k-1]*v[k-1];
		}
		t1=2/t1;
		
		
		//��Aת��ΪR ���ȶԵ�i�и�ֵ���ڶԺ�n-i�и��� 
		A[(i-1)*(n+1)]=-t;
		for(k=i+1;k<=n;k++)
			A[(k-1)*n+i-1]=0;
			
		for(j=i+1;j<=n;j++)
		{
			t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
			for(k=i;k<=n;k++)
				t2+=v[k-1]*A[(k-1)*n+j-1];
			t3=t1*t2;
			for(k=i;k<=n;k++)
				A[(k-1)*n+j-1]-=t3*v[k-1];
		} 
		
		//����y
		t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
		for(k=i;k<=n;k++)
			t2+=v[k-1]*y[k-1];
		t3=t1*t2;
		for(k=i;k<=n;k++)
			y[k-1]-=t3*v[k-1];
		
		//����Q
		for(j=1;j<=n;j++)
		{
			t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
			for(k=i;k<=n;k++)
				t2+=v[k-1]*Q[(k-1)*n+j-1];
			t3=t1*t2;
			for(k=i;k<=n;k++)
				Q[(k-1)*n+j-1]-=t3*v[k-1];
		}
		 	
		
		//�õ�λ��������¼househorder�����ÿһ����Ϣ 
		for(j=1;j<=n;j++)
		{
			t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
			for(k=i;k<=n;k++)
				t2+=v[k-1]*P[(k-1)*n+j-1];
			t3=t1*t2;
			for(k=i;k<=n;k++)
				P[(k-1)*n+j-1]-=t3*v[k-1];
		}
		printf("H(%d) = \n",i-1);
		MatPrintf(P,n);	
		
	}
	//�����A->R��I->Q,y->y(new); 
	MatT(Q,n);
	
}


 



































