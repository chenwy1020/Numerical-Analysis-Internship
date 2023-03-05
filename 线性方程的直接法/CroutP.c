#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(){
	// 相关函数声明 
	void CroutP(double A[], double P[], int n);
	void MatrixLower(double A[], double L[], int n);
	void MatrixUpper(double A[], double U[], int n);
	void MatriceMulti(double A[], double B[], double C[], int n, int k, int m);
	void MatrixPrint(double A[], int n);
	
	int i, j;
	
	// 测试数据
	double A[9]={2, 4, -2, 1, -1, 5, 4, 1, -2};
	double B[9]={2, 4, -2, 1, -1, 5, 4, 1, -2};
	double P[9]={0};
	// 输出 A
	printf("A =\n");
	MatrixPrint(A, 3);
	
	// 带行交换的 Crout 分解
	CroutP(A, P, 3);
	
	// 输出 A*
	printf("nA =\n");
	MatrixPrint(A, 3);
		 
	// 输出下三角部分
	double L[9];
	MatrixLower(A, L, 3);
	printf("L =\n");
	MatrixPrint(L, 3);	
	
	// 输出单位上三角部分 
	double U[9];
	MatrixUpper(A, U, 3);
	printf("U =\n");
	MatrixPrint(U, 3);	 
	
	// 输出行变换 P
	printf("P =\n");
	MatrixPrint(P, 3); 
	
	// 输出 L*U
	double LU[9];
	MatriceMulti(L, U, LU, 3,3,3);
	printf("\nL*U =\n");
	MatrixPrint(LU, 3); 
	
	// 输出 P*A
	double PA[9];
	MatriceMulti(P, B, PA, 3, 3, 3);
	printf("\nP*A =\n");	 
	MatrixPrint(PA, 3); 
		
	return 0;
}

// 带行交换的 Crout 算法做 LU 分解
// P 的输入为单位矩阵 
void CroutP(double A[], double P[], int n){
	int i, j, k, m;
	double temp;
	int VecP[n];
	
	// 对 VecP 初始化
	for(i=0; i<n; i++){ VecP[i]=i;}  
	
	for(i=0; i<n; i++){
		// 选主元
		m=i; temp=fabs(A[i*n+i]);
		for(k=i+1; k<n; k++){
			if(temp<fabs(A[k*n+i])){
				temp=fabs(A[k*n+i]);
				m=k;
			}
		} 
		
		// 换主元
		for(k=0; k<n; k++){
			temp=A[m*n+k]; A[m*n+k]=A[i*n+k];
			A[i*n+k]=temp;
		} 
		// 更新 P 
		temp=VecP[m]; VecP[m]=VecP[i]; VecP[i]=temp; 
		 
		// 生成矩阵 L 并存储到 A 的下三角部分 
		for(k=i; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[k*n+i]=A[k*n+i]-A[k*n+j]*A[j*n+i]; 
			}
		}
	
		// 生成矩阵 U 并存储到 A 的上三角部分
		for(k=i+1; k<n; k++){
			for(j=0; j<=i-1; j++){
				A[i*n+k]=A[i*n+k]-A[j*n+k]*A[i*n+j];
			}
			A[i*n+k]=A[i*n+k]/A[i*n+i];
		}	 
	} 
	
	// 生成行变换矩阵 P 
	for(i=0; i<n; i++){
		P[i*n+VecP[i]]=1;
	} 
} 

// 获取下三角部分
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

// 获取上三角部分 
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

// 矩阵乘矩阵 C=AB
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

// 矩阵输出
void MatrixPrint(double A[], int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%lf ", A[i*n+j]);
		}
		printf("\n");
	}
} 

