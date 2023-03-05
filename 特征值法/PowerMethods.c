#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
	
	// ��������
	void MatrixVectorMultiI(double A[], double a[], double b[], int n, int m);
	void Initialization(double A[], int n, int m);
	int MaxComponent(double A[], int n);
	void VecScalarMul(double A[], double B[], double a, int n);
	double VecDiff(double A[], double B[], int n);
	double PowerMethodA(double A[], double z[], double VecY[], int n, double eps, int K);
 
	int i, j, k, n, K;

	// �������Ľ� 
	scanf("%d", &n);
	double A[n*n], z[n], y[n], lambda, eps;
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

	// ������㾫�ȼ�����������
	scanf("%lf %d", &eps, &K); 
	
	// ���û������ݷ� 
	lambda=PowerMethodA(A, z, y, n, eps, K);
	
	// ������
	printf("%.4lf\n", lambda);
	for(i=0; i<n; i++){
		printf("%.4lf ", y[i]);
	}

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

// ��ʼ�� 
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


// �������ݷ���lambda_1>lambda_2
//	���ذ�ģ�������ֵ lambda
//	���룺
//		A[]: n-by-n ʵ���� 
//		z[]: ��ʼ���������������������� 
//		eps: ���㾫�� 
//		K: ���������� 
double PowerMethodA(double A[], double z[], double VecY[], int n, double eps, int K){
	int i, j, k=1;
	double err=1.;
	double m, temp;
	
	// y=Az
	MatrixVectorMultiI(A, z, VecY, n, n);
		
	// m=max(y_k)
	j=MaxComponent(VecY, n);
	m=VecY[j];
	temp=m;
			
	// z=y/m
	VecScalarMul(VecY, z, 1./m, n);
				
	while(k<K && err>eps){
		// y=Az
		MatrixVectorMultiI(A, z, VecY, n, n);
	
		// m=max(y_k)
		j=MaxComponent(VecY, n);
		m=VecY[j];
	
		// �������: ��ʽһ 
		err=fabs(m-temp);
				
		// ���£�z=y/m
		VecScalarMul(VecY, z, 1./m, n);
		
		// ���� 
		temp=m;	
		
		k=k+1;	
	}
	
	return m;
}



