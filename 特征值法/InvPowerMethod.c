#include<stdio.h>
#include<math.h>

int main(){
	double InvPowerMethodr1(double A[],double y[],double z[],int n,int K,double epsilon,double p);
	double InvPowerMethodr2(double A[],double y[],double z[],int n,int K,double epsilon,double p);
	void MatPrintf(double Q[],int m,int n);
	void MatCon(double Q[],double z[],int n);
	
	int n,i,K;
	//scanf("%d",&n);
	//printf("%d\n",n);
	
	//double A[n*n],z[n],y[n];
	double A[9]={2,-1,0,0,2,-1,0,-1,2},z[3]={0,0,1},y[3];
	
	double epsilon,m,p;
	n=3;  K=50;  epsilon=0.01;  p=2.93;
	/*
	//���� 
	for(i=0;i<n*n;i++){
		scanf("%lf",A+i);
	}
	//MatPrintf(A,n,n);
	for(i=0;i<n;i++){
		scanf("%lf",z+i);
	}
	//MatPrintf(z,1,n); 
	scanf("%lf",&p);
	//printf("%.8lf\n",p);	
	scanf("%d",&K);
	//printf("%d\n",K);
	scanf("%lf",&epsilon);
	//printf("%.8lf\n",epsilon);
	*/
	//���
	double A0[n*n],z0[n],y0[n];
	MatCon(A,A0,n*n);
	MatCon(z,z0,n);
	
	m=InvPowerMethodr2(A,y,z,n,K,epsilon,p);
	m=1/m+p;
	printf("%lf\n",m);
	
	m=InvPowerMethodr1(A0,y0,z0,n,K,epsilon,p);
	for(i=0;i<3;i++){
		printf("%lf ",z0[i]);
	}
	
}

//���ݷ�  
//r=fabs(m-t)
double InvPowerMethodr1(double A[],double y[],double z[],int n,int K,double epsilon,double p){
	int Vecmax(double v[],int n);//�����ľ���ֵ���ķ���
	void Doolittle(double A[], int n);// Doolittle �㷨�� LU �ֽ�
	void MatrixUpper(double A[], double U[], int n);// ��ȡ�����ǲ��� 
	void MatrixLower(double A[], double L[], int n);// ��ȡ��λ�����ǲ���
	void LUSolver(double L[],double U[],double x[],double b[],int n);//��� LUx=b 
	void MatPrintf(double Q[],int m,int n);
	
	int i,k,j;
	double m,r,t;
	double L[n*n],U[n*n];
	
	//��ʼ��
	for(i=0;i<n;i++){
		A[i*n+i]-=p;
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
	
	return m; 
}

//���ݷ�
//r=fabs(1/m-1/t)
double InvPowerMethodr2(double A[],double y[],double z[],int n,int K,double epsilon,double p){
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
		
		r=fabs(1./m-1./t);//�в� 
		
		if(r<epsilon){
			break;
		}
		
		t=m;//����t
	}
	MatCon(P,A,n*n);
	return m; 
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




