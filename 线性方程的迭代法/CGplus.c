#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

// �������������
double VecNorm_inf(double a[], int n){
	int i;
	double temp, norm=fabs(a[0]);
	
	for(i=1; i<n; i++){
		temp=fabs(a[i]);
		if(norm<temp){	norm=temp; }
	}
	
	return norm;
} 

// �������Ķ����� 
double VecNorm_2(double a[], int n){
	int i;
	double temp, norm=0;
	
	for(i=0; i<n; i++){
		norm=norm+a[i]*a[i];
	}
	
	return norm;
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

// �����½������ Ax=b, A Ϊ�Գ���������
int SteepestDecentSolver(double A[], double b[], double x[], int n, double epsilon, int K){
	double r[n], Ar[n];
	double ak;
	int i, j, k=0;
	double err;
	
	// �����ʼ�в� r0=b-Ax0 
	MatrixVectorMultiI(A, x, Ar, n, n);
	for(i=0; i<n; i++){
		r[i]=b[i]-Ar[i];
	}
	err=VecNorm_inf(r, n);
	
	while(err>epsilon && k<K ){
		// ���� Ar
		MatrixVectorMultiI(A, r, Ar, n, n); 
		
		// ���� alpha_k
		ak=VectorsMultiI(r, r, n)/VectorsMultiI(Ar, r, n); 
		
		// ���µ����� 
		for(i=0; i<n; i++){	x[i]=x[i]+ak*r[i];	}
		
		// ���²в�
		for(i=0; i<n; i++){	r[i]=r[i]-ak*Ar[i];	} 
		
		k=k+1;
		err=VecNorm_inf(r, n);
	}
	
	return k;	
}

// ��С��������� Ax=b, A Ϊ�Գ���������
int MinResidualSolver(double A[], double b[], double x[], int n, double epsilon, int K){
	double r[n], Ar[n];
	double ak;
	int i, j, k=0;
	double err;
	
	// �����ʼ�в� r0=b-Ax0 
	MatrixVectorMultiI(A, x, Ar, n, n);
	for(i=0; i<n; i++){
		r[i]=b[i]-Ar[i];
	}
	err=VecNorm_inf(r, n);
	
	while(err>epsilon && k<K ){
		// ���� Ar
		MatrixVectorMultiI(A, r, Ar, n, n); 
		
		// ���� alpha_k
		ak=VectorsMultiI(Ar, r, n)/VectorsMultiI(Ar, Ar, n); 
		
		// ���µ����� 
		for(i=0; i<n; i++){	x[i]=x[i]+ak*r[i];	}
		
		// ���²в�
		for(i=0; i<n; i++){	r[i]=r[i]-ak*Ar[i];	} 
		
		k=k+1;
		err=VecNorm_inf(r, n);
	}
	
	return k;	
}

// �������ݶ���� Ax=b, A Ϊ�Գ���������
int CGSolver(double A[], double b[], double x[], int n, double epsilon, int K){
	double r[n], p[n], Ap[n];
	double ak, betak;
	int i, j, k=0;
	double err, temp;
	
	// �����ʼ�в� r0=b-Ax0 
	MatrixVectorMultiI(A, x, Ap, n, n);
	for(i=0; i<n; i++){
		r[i]=b[i]-Ap[i];
		p[i]=r[i];
	}
	err=VecNorm_inf(r, n);
	//err=VecNorm_2(r, n);	
	
	while(err>epsilon && k<K ){
		// ���� Ap
		MatrixVectorMultiI(A, p, Ap, n, n); 
		
		// ���� Ap_k
		temp=VectorsMultiI(Ap, p, n);
		
		// ���� alpha_k
		ak=VectorsMultiI(r, p, n)/temp; 
		
		// ���µ����� 
		for(i=0; i<n; i++){	x[i]=x[i]+ak*p[i];	}
		
		// ���²в�
		for(i=0; i<n; i++){	r[i]=r[i]-ak*Ap[i];	} 

		// ���� beta_k
		betak=-VectorsMultiI(r, Ap, n)/temp; 

		// ���� p
		for(i=0; i<n; i++){	p[i]=r[i]+betak*p[i];	} 
						
		k=k+1;
		err=VecNorm_inf(r, n);
		//err=VecNorm_2(r, n);	
	}
	
	return k;	
}
 
int main(){
	int i, j;
	
	// ��������
	double A[16]={13, 9, 9, 11, 9, 11, 6, 9, 9, 6, 12, 7, 11, 9, 7, 10};
	double b[4]={42,35,34,37};
	double epsilon=0.000001;
	int K=2000;

	// ��ҵ
	int k;
	double x[4]={0, 0, 0, 0};
	
	// �����½��� 
	//k=SteepestDecentSolver(A, b, x, 4, epsilon, K);
	
	// ��С������ 
	//k=MinResidualSolver(A, b, x, 4, epsilon, K);	
	
	// �����ݶȷ�
	k=CGSolver(A, b, x, 4, epsilon, K);
	
	// ������ 
	printf("step = %d\n", k);
	printf("x =\n");
	for(i=0; i<4; i++){
		printf("%lf\n", x[i]);
	}	 
		
	return 0;
}

