#include<stdio.h>
#include<math.h>

int main(){
	//�������� 
	int QRMethod(double A[],double lambda[],int n,int K,double epsilon);
	void MatPrintf(double Q[],int m,int n);
	double InvPowerMethodr1(double A[],double y[],double z[],int n,int K,double epsilon,double p);
	
	int n=4,k,i;
	double A[16]={13,9,9,11,9,11,6,9,9,6,12,7,11,9,7,10};
	double z[4]={1,0,0,0},y[4];
	double lambda[4];
	double epsilon=0.000001,K=10000;
	
	k=QRMethod(A,lambda,n,K,epsilon);
	printf("QRMethod����������%d\n",k);
	MatPrintf(lambda,1,n);
	printf("\n"); 
	
	for(i=0;i<n;i++){
		printf("���ݷ��� %d ��ֵ����ֵ��%lf\n",i+1,lambda[i]);
		InvPowerMethodr1(A,y,z,n,K,epsilon,lambda[i]);
		printf("���ݷ��� %d ��ֵ��������",i+1);
		MatPrintf(z,1,n);
		printf("\n"); 
	}
	
}

//QR�����㷨 
int QRMethod(double A[],double lambda[],int n,int K,double epsilon){
	void MatMul(double A[],double B[],double y[],int m,int n,int p);
	void Householder(double A[],double Q[],double R[],int n);
	void MatPrintf(double Q[],int m,int n);
	void MatCon(double Q[],double z[],int n);
	
	double t,r;
	double Q[n*n],R[n*n],A0[n*n];
	int i,k;
	//��ʼ��
	MatCon(A,A0,n*n); 
	for(i=0;i<n;i++){
		lambda[i]=A[i*n+i];
	}

	for(k=2,r=1;k<K && r>epsilon;k++){
		//A=QR
		Householder(A,Q,R,n);
		
		//���� A_k+1=R*Q 
		MatMul(R,Q,A,n,n,n);
		
		//����в�
		r=0;
		for(i=1;i<=n;i++){
			t=A[(i-1)*n+i-1];
			r+=fabs(t-lambda[i-1]);
			lambda[i-1]=t;		
		}
		if(r<=epsilon) break;		
	}
	MatCon(A0,A,n*n);
	return k;
	

}

//Householder�任 
void Householder(double A[],double Q[],double R[],int n){
	void MatT(double Q[],int n);
	void MatCon(double Q[],double z[],int n);
	
	int i,j,k,i1,j1;
	double t,t1=0,t2=0,t3=0,v[n];
	double P[n*n];
	
	//��ʼ�� 
	MatCon(A,P,n*n); 
	for(i1=1;i1<=n;i1++)
		for(j1=1;j1<=n;j1++)
		{
			Q[(i1-1)*n+j1-1]=0;
			Q[(i1-1)*(n+1)]=1; 
			R[(i1-1)*n+j1-1]=0;
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
		
	}
	//�����A->R��I->Q; 
	MatT(Q,n);
	MatCon(A,R,n*n);
	MatCon(P,A,n*n);
	
}

//���ݷ�  ����� p ������������� y 
//r=fabs(m-t)
double InvPowerMethodr1(double A[],double y[],double z[],int n,int K,double epsilon,double p){
	int Vecmax(double v[],int n);//�����ľ���ֵ���ķ���
	void Doolittle(double A[], int n);// Doolittle �㷨�� LU �ֽ�
	void MatrixUpper(double A[], double U[], int n);// ��ȡ�����ǲ��� 
	void MatrixLower(double A[], double L[], int n);// ��ȡ��λ�����ǲ���
	void LUSolver(double L[],double U[],double x[],double b[],int n);//��� LUx=b 
	void MatPrintf(double Q[],int m,int n);
	void MatCon(double Q[],double z[],int n);
	
	int i,k,j;
	double m,r,t;
	double L[n*n],U[n*n],P[n*n];
	
	//��ʼ��
	MatCon(A,P,n*n);
	for(i=0;i<n;i++){
		A[i*n+i]-=p;
		y[i]=0;
		z[i]=0;
		z[0]=1;
	}
	
	Doolittle(A,n);
	MatrixUpper(A,U,n);
	MatrixLower(A,L,n);
	//MatPrintf(L,n,n);
	//MatPrintf(U,n,n);
	LUSolver(L,U,y,z,n);
	j=Vecmax(y,n);
	m=y[j];
	t=m;
	
	for(k=2;k<=K;k++){
		
		for(i=0;i<n;i++){
			z[i]=y[i]/m;
		}//���� z
		
		LUSolver(L,U,y,z,n);//���Ay=z
		
		j=Vecmax(y,n);
		m=y[j];//����ֵ���ķ���
		
		r=fabs(m-t);//�в� 
		
		if(r<epsilon){
			break;
		}
		
		t=m;//����t
	}
	MatCon(P,A,n*n);
	//return m; 
}

// Doolittle �㷨�� LU �ֽ�
void Doolittle(double A[], int n){
	int i, j, k;
	
	for(i=0; i<n; i++){
		// ���ɾ��� U ���洢�� A �������ǲ��� 
		for(k=i; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[i*n+k]=A[i*n+k]-A[i*n+j]*A[j*n+k]; 
			}
		}
	
		// ���ɾ��� L ���洢�� A �������ǲ���
		for(k=i+1; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[k*n+i]=A[k*n+i]-A[k*n+j]*A[j*n+i];
			}
			A[k*n+i]=A[k*n+i]/A[i*n+i];
		}	 
	} 
} 

//����ת�� 
void MatT(double Q[],int n){
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
void MatPrintf(double Q[],int m,int n){
	int i,j;
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++){
			printf("%lf\t",Q[(i-1)*n+j-1]);
		}
		printf("\n");
	}
} 

//����̳�
void MatCon(double Q[],double z[],int n){
	int i;
	for(i=0;i<n;i++)
		z[i]=Q[i];
} 

//����˷�
void MatMul(double A[],double B[],double y[],int m,int n,int p){
	int i,j,k;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			y[(i-1)*p+j-1]=0;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			for(k=1;k<=n;k++)
				y[(i-1)*p+j-1]+=A[(i-1)*n+k-1]*B[(k-1)*p+j-1];
}

//��� LUx=b 
void LUSolver(double L[],double U[],double x[],double b[],int n){
	void UpTriSys(double U[],double x[],double y[],int n);
	void DwTriSys(double L[],double x[],double y[],int n);
	double p[n];
	int i;
	DwTriSys(L,x,b,n);
	for(i=0;i<n;i++){
		p[i]=x[i];
	}
	UpTriSys(U,x,p,n);	
}

//UΪ�����Ǿ������ Ux=y 
void UpTriSys(double U[],double x[],double y[],int n){
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
void DwTriSys(double L[],double x[],double y[],int n){
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

// ��ȡ��λ�����ǲ���
void MatrixLower(double A[], double L[], int n){
	int i, j;
	
	for(i=0; i<n; i++){	L[i*n+i]=1;}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			L[i*n+j]=0;
			L[j*n+i]=A[j*n+i];
		}
	}
}

// ��ȡ�����ǲ��� 
void MatrixUpper(double A[], double U[], int n){
	int i, j;
	
	for(i=0; i<n; i++){	U[i*n+i]=A[i*n+i];}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			U[j*n+i]=0;
			U[i*n+j]=A[i*n+j];
		}
	}
}

//�����ľ���ֵ���ķ���
int Vecmax(double v[],int n){
	double t;
	int i,j;
	j=0;
	t=fabs(v[0]);
	for(i=0;i<n;i++){	
		if(t<fabs(v[i])){
			t=fabs(v[i]);
			j=i;
		}
	}
	
	return j;
} 

// �����ʼ�� 
void Initialization(double A[], int n, int m){
	int i;
	for(i=0; i<n*m; i++){ A[i]=0.; }	
}

