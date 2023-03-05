#include<stdio.h>
#include<math.h>

// ��˹����Ԫ��ȥ�� 
int main(){
	// ��Ӧ�ӳ���
	void GaussianEliminationB(double A[], double b[], int n);
	void UpTriSys(double A[], double x[], double y[], int n);
	void MatrixPrint(double A[], int n, int m);
	 
	// ��������
	int i, j;
	double A[9]={2, 4, -2, 1, -1, 5, 4, 1, -2}; 
	double B[9]={2, 4, -2, 1, -1, 5, 4, 1, -2}; 
	double x[3]={0}; 
	double b[3]={6, 0, 2};
	double temp;
	
	// ������� A
	printf("A =\n");
	MatrixPrint( A, 3, 3 );
	
	// ������� b
	printf("b =\n");
	MatrixPrint( b, 1, 3); 
	
	// Gauss ����Ԫ��Ԫ
	GaussianEliminationB(A, b, 3);
	printf("nA =\n");
	MatrixPrint( A, 3, 3);
	
	printf("nb =\n");
	MatrixPrint( b, 1, 3);
	
	// ���������ϵͳ
	UpTriSys(A, x, b, 3);
	
	// ��� x
	printf("x =\n");
	MatrixPrint(x, 1, 3);
	
	// ��� nA*x
	printf("nA*x =\n");
	for(i=0; i<3; i++){
		temp=0;
		for(j=0; j<3; j++){
			temp=temp+A[i*3+j]*x[j];
		}
		printf("%lf\n", temp);
	} 
	
	// ��� A*x
	printf("\nA*x =\n");
	for(i=0; i<3; i++){
		temp=0;
		for(j=0; j<3; j++){
			temp=temp+B[i*3+j]*x[j];
		}
		printf("%lf\n", temp);
	} 	 

	
	return 0;
}


// Gauss ��Ԫ��ȥ�� 
void GaussianEliminationB(double A[], double b[], int n){
	int i, j, k, r;
	double l, temp;
	
	// ��Ԫ��Ԫ 
	for(i=0; i<n-1; i++){
		// ����Ԫ
		r=i; temp=fabs(A[i*n+i]);
		for(k=i+1; k<n; k++){
			if(temp<fabs(A[k*n+i])){
				temp=fabs(A[k*n+i]);
				r=k;
			}
		} 
		
		if(r!=i){
			// ����Ԫ
			for(k=i; k<n; k++){
				temp=A[r*n+k]; 
				A[r*n+k]=A[i*n+k];
				A[i*n+k]=temp;
			} 
			// ���Ҷ�����
			temp=b[r]; b[r]=b[i]; b[i]=temp; 
		}
		
		// ��Ԫ 
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

// ��������� A[i, j]<0.000001, ����Ϊ +0
void MatrixPrint(double A[], int n, int m){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			if(fabs(A[i*m+j])<0.000001){
				A[i*m+j]=0;
			}
			printf("%lf ", A[i*m+j]);
		}
		printf("\n");
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

