#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

double f(double x);
double basis_function(double x,int i);
double p(double x,double *a);

void BestSquareApproximationFunction(int n, int m, double left, double right);

double Gaussg(double left, double right,int i,int j);
double Gaussb(double left, double right,int i);
double Gaussfp(double left, double right, double *a);

void uniform_partition(int m, double left, double right, double *xs);
void assemble_matrix(int n, double *x, int m, double **A); 
void right_side(int n, double *x, int m, double *b);
void ColElim(int n, double **A, double *b, double *x);

void output(int n,int m, double *x, double *a);

int main(){
	
	double left = -1.0, right = 1.0;
	int n = 16;
	int m=5;
	
	//Ӧ��������ƽ���ƽ����� 
	
	
	return 0;
}

//ԭ���� 
double f(double x){

}
//������ 
double basis_function(double x,int i){

}
//����p(x) 
double p(double x,double *a){
	
	double temp=0.0;
	
	temp=;
	
	return temp;
}
//
void BestSquareApproximationFunction(int n, int m, double left, double right){
	int i,j;
	double x[n+1];
	double temp;
	double **A;
	double b[m],a[m];
	
	//��ʼ�� A b 
	
	
	//�������� 


	//��ȡ���� 


	//��ȡ�Ҷ����� 


	//����Ԫ������Է��� 


	//��� 
	

	//�ͷ�A�ڴ� 
	
	
}

//����Gram �����õĺ���  basis_function(i)*basis_function(j)
double Gaussg(double left, double right,int i,int j){
	double x0,x1,temp;
	
	x0=; 
	x1=;
	
	temp=;
	
	return temp;
	
} 
//�Ҷ������õĺ���  f*basis_function
double Gaussb(double left, double right,int i){
	double x0,x1,temp=0.0;
	
	x0=;
	x1=;
	
	temp=;
	
	return temp;
	
} 
//������� e ����ĺ��� (f-p)^2
double Gaussfp(double left, double right, double *a){
	double x0,x1,temp;
	
	x0=;
	x1=;
	
	temp=;
	
	return temp;
	
} 

//�������� 
void uniform_partition(int m, double left, double right, double *xs){
	/*
	�ó������ڶ�������о����ʷ�, �����ʷֵ���������˵� 
	
	m ��ʾ�ʷֵ���� 
	left ��ʾ������˵�
	right ��ʾ�����Ҷ˵�
	xs ��ʾ�ʷֵ����� 
	*/	
	int i;
	double h;  
	
	//h��ʾ�ʷֲ��� 
	h = (right-left) / m;
	
	//ÿ���ʷֵ����꼴Ϊ��˵�+����*���� 
	for(i=0;i<m+1;i++){
		xs[i] = left + h*i;
	}
	
}

//��ȡ���� 
void assemble_matrix(int n, double *x, int m, double **A){
	int i,j,k;//ѭ������ 
	double temp;

	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			temp=0.0;
			//����ѭ�� 
			//����Gaussg ����temp ����ֵ��A[i][j]
			
			//printf("%lf  ",A[i][j]);    //������֤ 
		}
	} 
	
} 

//��ȡ�Ҳ����� 
void right_side(int n, double *x, int m, double *b){
	int i,k;
	double temp;
	
	for(i=0;i<m;i++){
		temp=0.0;
		//����ѭ�� 
		//����Gaussb����temp ����ֵ��b[i]
	}
}
 
void output(int n,int m, double *x, double *a){
	
	int i;
	double e=0;
	
	printf("���ƽ���ƽ�����Ϊ: \n"); 
	printf("%+lf %+lf x %+lf x^2 %+lf sin(2x) %+lf cos(2x)\n",a[0],a[1],a[2],a[3],a[4]);
	
	//����ѭ��������Gaussfp����e�Ĵ�С���� 
	
	e=sqrt(e);
	printf("���Ϊ: \n%lf\n", e);
	
	return;
}
 
//����Ԫ��ȥ���������Է��� 
void ColElim(int n, double **A, double *b, double *x){ 
    int i,j,k,r,kk,ik,ki,ri;
    double iMax, t, Aii;
          
    for(k=0; k<n-1; k++)    { 
       	r = k;
       	kk = k*n+k;
       	iMax = fabs(A[k][k]);
       	for(i=k+1; i<n; i++){
          	t = fabs(A[i][k]);
          	if(t>iMax){
             	r = i;
             	iMax = t;                       
          	}
       	}   // ѡ����Ԫ
       	if(r!=k){
          	for(i=k; i<n; i++){
             	ki = k*n+i;
             	ri = r*n+i;             
             	t = A[k][i];
             	A[k][i] = A[r][i];
             	A[r][i] = t;
          	} // �������� A �� r,k ����Ԫ��
          	t = b[k];
          	b[k] = b[r];
          	b[r] = t;  // ���� b �� r,k ����Ԫ�� 
       	}

	   	if(fabs(A[k][k])<1e-12){
          	printf("fail\n"); 
          	return;
       	}
       	for(i=k+1; i<n; i++){
          	ik=i*n+k;
          	A[i][k] /= A[k][k];
          	b[i] -= A[i][k]*b[k];  
          	for(j=k+1; j<n; j++){ 
             	A[i][j] -= A[i][k]*A[k][j];
            } 
          	A[i][k] = 0.0;
       	}
    }
        
    kk = k*n+k;
    if(fabs(A[k][k])<1e-12){
       	printf("fail\n"); 
       	return;
    }  
    
    Aii = A[n-1][n-1];
    if(fabs(Aii)<1e-12){
       	printf("fail\n"); 
       	return;
    }
    else{ 
        x[n-1] = b[n-1];
        if(Aii!=1.0){ 
           x[n-1] /= Aii;
        } 
    }
        
    for(i = n-2; i >= 0; i--){
        Aii = A[i][i];
        if(fabs(Aii)<1e-12){
           printf("fail\n"); 
           return;
        }
        else{
           	x[i] = 0.0;   
           	for(j = i+1; j < n; j++){   
              	x[i] += A[i][j]*x[j];
            } 
           	x[i] = b[i]-x[i];
           	if(Aii!=1.0){ 
              	x[i] /= Aii;
        	}
        }
    }
    
    return;
}
