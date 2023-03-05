#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// ԭ��λ�Ʒ��ݷ���
int main(){
	
	// ��������
	void MatrixVectorMultiI(double A[], double a[], double b[], int n, int m);
	double VectorsMultiI(double a[], double b[],  int n);
	void Initialization(double A[], int n, int m);
	int MaxComponent(double A[], int n);
	void VecScalarMul(double A[], double B[], double a, int n);
	double VecDiff(double A[], double B[], int n);
	void DoolittleP(double A[], double P[], int n);
	void MatrixLower(double A[], double L[], int n);
	void MatrixUpper(double A[], double U[], int n);
	void LowTriSys(double A[], double x[], double y[], int n);
	void UpTriSys(double A[], double x[], double y[], int n);
	double InvPowerMethodB(double A[], double z[], double VecY[], int n, double eps, int K, double lambda0);
 		
	int i, j, k, n, K;

	// �������Ľ� 
	scanf("%d", &n);
	double A[n*n], z[n], y[n], lambda, lambda0, eps;
	Initialization(A, n, n);
	Initialization(z, n, 1);	
	Initialization(y, n, 1);	

	// �������Ԫ��
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			scanf("%lf", &A[i*n+j]);
		}
	} 
	
	// �����ʼ����
	for(i=0; i<n; i++){
		scanf("%lf", &z[i]);
	} 
		
	// ���� lambda0	
	scanf("%lf", &lambda0);
	
	// ������㾫�ȼ�����������a
	scanf("%d %lf", &K, &eps); 

	// ���÷��ݷ� 
	lambda=InvPowerMethodB(A, z, y, n, eps, K, lambda0);
	printf("%lf\n", lambda);
	for(i=0; i<n; i++){
		printf("%lf ", z[i]);
	}
	printf("\n");
	
	return 0;
}


// ��������������I b=Aa
void MatrixVectorMultiI(double A[], double a[], double b[], int n, int m){
	int i, j;
	double c;
	for(i=0; i<n; i++){
		c=0;
		for(j=0; j<m; j++){
			c=c+A[i*m+j]*a[j];
		}
		b[i]=c;
	}
} 

// ���������˷�I c=ab^T 
double VectorsMultiI(double a[], double b[],  int n){
	int i;
	double c=0;
	for(i=0; i<n; i++){
		c=c+a[i]*b[i];
	}
	
	return c;
}

// �����ʼ�� 
void Initialization(double A[], int n, int m){
	int i;
	for(i=0; i<n*m; i++){ A[i]=0.; }	
}

// �ҵ����� A ����ֵ���ķ��� 
int MaxComponent(double A[], int n){
	int i, k;
	double temp;
	temp=fabs(A[0]);
	k=0;
	
	for(i=1; i<n; i++){
		if(temp<fabs(A[i])){
			k=i;
			temp=fabs(A[i]);
		}
	}
	
	return k;
}


// ���������˷�
void VecScalarMul(double A[], double B[], double a, int n){
	int i;
	for(i=0; i<n; i++){
		B[i]=A[i]*a;
	}
} 

// ����������ķ���
double VecDiff(double A[], double B[], int n){
	int i;
	double temp=0;
	for(i=0; i<n; i++){
		temp=fabs(A[i]-B[i]);
	}
	
	return temp;
} 


// �����н��� Doolittle �㷨�� LU �ֽ�
void DoolittleP(double A[], double P[], int n){
	int i, j, k, m;
	double temp;
	int VecP[n];
	
	// �� VecP ��ʼ��
	for(i=0; i<n; i++){ VecP[i]=i;}  
	
	for(i=0; i<n; i++){
		// ѡ��Ԫ
		m=i; temp=fabs(A[i*n+i]);
		for(k=i+1; k<n; k++){
			if(temp<fabs(A[k*n+i])){
				temp=fabs(A[k*n+i]);
				m=k;
			}
		} 
		
		// ����Ԫ
		for(k=0; k<n; k++){
			temp=A[m*n+k]; A[m*n+k]=A[i*n+k];
			A[i*n+k]=temp;
		} 
		// ���� P 
		temp=VecP[m]; VecP[m]=VecP[i]; VecP[i]=temp; 	
	

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
	
	// �����б任���� P 
	for(i=0; i<n; i++){
		P[i*n+VecP[i]]=1;
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

// �����Ǿ������ 
void LowTriSys(double A[], double x[], double y[], int n){
	int i, j;
	for(i=0; i<n; i++){
		x[i]=y[i]/A[i*n+i];
		for(j=i+1; j<n; j++){
			y[j]=y[j]-x[i]*A[j*n+i];
		}
	} 
}


// �����Ǿ������ 
void UpTriSys(double A[], double x[], double y[], int n){
	int i, j;
	for(i=n-1; i>=0; i--){
		x[i]=y[i]/A[i*n+i];
		for(j=0; j<=i-1; j++){
			y[j]=y[j]-x[i]*A[j*n+i];
		}
	} 
}

// ԭ��λ�Ʒ��ݷ���lambda_N<lambda_N-1
//	���ô��б任�� Doolittle �ֽ����Ԥ���� 
//	���ذ�ģ�������ֵ lambda
//	���룺
//		A[]: n-by-n ʵ���� 
//		z[]: ��ʼ����
//		VecY[]: ���������������� 
//		eps: ���㾫�� 
//		K: ���������� 
//      lambda0: ��ʼ���� 
double InvPowerMethodB(double A[], double z[], double VecY[], int n, double eps, int K, double lambda0){
	int i, j, k=1;
	double err=1.;
	double m, temp, Pz[n], tempx[n];
	double P[n*n], L[n*n], U[n*n];
	Initialization(P, n, n);
	Initialization(L, n, n);
	Initialization(U, n, n);	

	// �����б任�� Doolittle �ֽ� A ��Ԥ����		
	for(i=0; i<n; i++){	A[i*n+i]=A[i*n+i]-lambda0; }
	DoolittleP(A, P, n);
	MatrixLower(A, L, n);
	MatrixUpper(A, U, n);

	// z=Ay
	MatrixVectorMultiI(P, z, Pz, n, n);	
	LowTriSys(L, tempx, Pz, n);
	UpTriSys(U, VecY, tempx, n);
		
	// m=max(y_k)
	j=MaxComponent(VecY, n);
	m=VecY[j];
	temp=m;

	k=k+1;
	
	// z=y/m
	VecScalarMul(VecY, z, 1./m, n);
				
	while(k<K && err>eps){
		// z=Ay
		MatrixVectorMultiI(P, z, Pz, n, n);	
		LowTriSys(L, tempx, Pz, n);
		UpTriSys(U, VecY, tempx, n);
		
		// m=max(y_k)
		j=MaxComponent(VecY, n);
		m=VecY[j];

		// �������: ��ʽһ 
		err=fabs(1./m-1./temp); 	
				
		// ���£�z=y/m
		VecScalarMul(VecY, z, 1./m, n);
		
		// ���� 
		temp=m;	
		
		k=k+1;	
	}
	
	return 1/m+lambda0;
}



