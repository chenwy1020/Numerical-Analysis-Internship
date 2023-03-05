#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(){
	// ��غ������� 
	void Crout(double A[], int n);
	void MatrixLower(double A[], double L[], int n);
	void MatrixUpper(double A[], double U[], int n);
	void MatriceMulti(double A[], double B[], double C[], int n, int k, int m);
	void MatrixPrint(double A[], int n);
	
	int i, j;
	
	// ��������
	double A[9]={2, 4, -2, 1, -1, 5, 4, 1, -2};
	// ��� A
	printf("A =\n");
	MatrixPrint(A, 3);
	
	// Crout �ֽ�
	Crout(A, 3);
	
	// ��������ǲ���
	double L[9];
	MatrixLower(A, L, 3);
	printf("L =\n");
	MatrixPrint(L, 3);	
	
	// �����λ�����ǲ��� 
	double U[9];
	MatrixUpper(A, U, 3);
	printf("U =\n");
	MatrixPrint(U, 3);	 
	
	// ��� L*U
	double LU[9];
	MatriceMulti(L, U, LU, 3,3,3);
	printf("\nL*U =\n");
	MatrixPrint(LU, 3); 
	
	return 0;
}

// Crout �㷨�� LU �ֽ�
void Crout(double A[], int n){
	int i, j, k;
	
	for(i=0; i<n; i++){
		// ���ɾ��� L ���洢�� A �������ǲ��� 
		for(k=i; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[k*n+i]=A[k*n+i]-A[k*n+j]*A[j*n+i]; 
			}
		}
	
		// ���ɾ��� U ���洢�� A �������ǲ���
		for(k=i+1; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[i*n+k]=A[i*n+k]-A[j*n+k]*A[i*n+j];
			}
			A[i*n+k]=A[i*n+k]/A[i*n+i];
		}	 
	} 
} 

// ��ȡ�����ǲ���
void MatrixLower(double A[], double L[], int n){
	int i, j;
	
	for(i=0; i<n; i++){	L[i*n+i]=A[i*n+i];}
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
	
	for(i=0; i<n; i++){	U[i*n+i]=1;}
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			U[j*n+i]=0;
			U[i*n+j]=A[i*n+j];
		}
	}
}

// ����˾��� C=AB
void MatriceMulti(double A[], double B[], double C[], int n, int k, int m){
	int i, j, w;
	double c;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			c=0;
			for(w=0; w<k; w++){
				c=c+A[i*k+w]*B[w*m+j];
			}
			C[i*m+j]=c;
		}
	}
} 

// �������
void MatrixPrint(double A[], int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%lf ", A[i*n+j]);
		}
		printf("\n");
	}
} 

