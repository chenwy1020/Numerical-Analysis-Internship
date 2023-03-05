#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(){
	// ��غ������� 
	void CroutP(double A[], double P[], int n);
	void MatrixLower(double A[], double L[], int n);
	void MatrixUpper(double A[], double U[], int n);
	void MatriceMulti(double A[], double B[], double C[], int n, int k, int m);
	void MatrixPrint(double A[], int n);
	
	int i, j;
	
	// ��������
	double A[9]={2, 4, -2, 1, -1, 5, 4, 1, -2};
	double B[9]={2, 4, -2, 1, -1, 5, 4, 1, -2};
	double P[9]={0};
	// ��� A
	printf("A =\n");
	MatrixPrint(A, 3);
	
	// ���н����� Crout �ֽ�
	CroutP(A, P, 3);
	
	// ��� A*
	printf("nA =\n");
	MatrixPrint(A, 3);
		 
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
	
	// ����б任 P
	printf("P =\n");
	MatrixPrint(P, 3); 
	
	// ��� L*U
	double LU[9];
	MatriceMulti(L, U, LU, 3,3,3);
	printf("\nL*U =\n");
	MatrixPrint(LU, 3); 
	
	// ��� P*A
	double PA[9];
	MatriceMulti(P, B, PA, 3, 3, 3);
	printf("\nP*A =\n");	 
	MatrixPrint(PA, 3); 
		
	return 0;
}

// ���н����� Crout �㷨�� LU �ֽ�
// P ������Ϊ��λ���� 
void CroutP(double A[], double P[], int n){
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
	
	// �����б任���� P 
	for(i=0; i<n; i++){
		P[i*n+VecP[i]]=1;
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

