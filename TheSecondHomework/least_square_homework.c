#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double least_square(int n, double *x, double *y, int m, double *a);
void assemble_matrix(int n, double *x, int m, double **A);
void right_side(int n, double *x, double *y, int m, double *b);
void basis_function(int n, double *x, int i, double *phi_i);
double dot(int n, double *vector1, double *vector2);
void output(int n, int m,double *x, double *y, double *a,double xs, double ys,double e); 
void ColElim(int n, double **A, double *b, double *x);
double compute_value(int m, double *a, double xs);

int main(){
	/*
	�ó�������������С���˷��������ƽ���ƽ�����ʽ
	
	x ��ʾ��ϵ�����
	y ��ʾ��ϵ㺯��ֵ
	a ��ʾ������Ķ���ʽϵ��
	n ��ʾ��ϵ����
	degree ��ʾ����ʽ����
	m ��ʾ����ʽϵ���ĸ���
	xs ��ʾ����� 
	ys ��ʾ�������Ϻ���ֵ 
	*/
	
	double x[] = {-1.0,-0.8,-0.6,-0.4,-0.2,0.0, 0.2, 0.4, 0.6, 0.8, 1.0};
	double y[] = {-0.8669,-0.2997,0.3430,1.0072,1.6416,2.2022,2.6558,2.9823,3.1755,3.2416,3.1974};
	double xs = 0.8;
	double ys,e;
	
	double *a;

 	int n = 11;
	int degree = 4;
	int m;
	
	//����ʽϵ������Ϊ����ʽ������1 
	m = degree + 1; 
	//Ϊ����ʽϵ�������ڴ� 
	a = (double *)malloc(sizeof(double)*m);
	
	//������С���˷�����ϵ��a 
	e = least_square(n, x, y, m, a);
	
	//����������Ϻ���ֵ 
	ys = compute_value(m, a, xs);
	
	
	//��������� 
	output(n, m, x, y, a, xs, ys,e);
	
	//�ͷ��ڴ� 
	free(a); 
	
	return 0;
}

double least_square(int n, double *x, double *y, int m, double *a){
	int i,j; 
	double **A;
	double b[m],e=0,r;
	
	//��ʼ�� A b 
	A = (double **)malloc(sizeof(double *)*(m));
	for(i=0; i<m; i++ ){
		A[i] = (double*)malloc(sizeof(double)*(m));
	}

	assemble_matrix(n,x,m,A);

	right_side(n,x,y,m,b);

	ColElim(m,A,b,a);
	
	for(i=0;i<n;i++){
		r=0;
		for(j=0;j<m;j++){
			r+=a[j]*pow(x[i],j);
		}
		e+=pow(r-y[i],2);
	}
	
	e = sqrt(e);
	
	return e;
	
	for( i=0; i<m; i++){
		free(A[i]);
	}
	free(A);
} 

//��ȡ���� 
void assemble_matrix(int n, double *x, int m, double **A){
	int i,j;
	double psi_i[n],psj_j[n];
	 
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			
			basis_function(n,x,i,psi_i);
			basis_function(n,x,j,psj_j);
			A[i][j]=dot(n,psi_i,psj_j);
			//printf("%lf  ",A[i][j]);
		}
	} 
	
} 

//��ȡ�Ҳ����� 
void right_side(int n, double *x, double *y, int m, double *b){
	int i;
	double psi[n];
	
	for(i=0;i<m;i++){
		basis_function(n,x,i,psi);
		b[i]=dot(n,y,psi);
	}
}
 
//���ɻ������� 
void basis_function(int n, double *x, int i, double *phi_i){
	int k;
	for(k=0;k<n;k++){
		phi_i[k]=pow(x[k],i);
	}
} 

//�����ڻ� 
double dot(int n, double *vector1, double *vector2){
	int i;
	double temp=0.0;
	
	for(i=0;i<n;i++){
		temp+=vector1[i]*vector2[i];
	}
	
	return temp;
	
} 

void output(int n,int m, double *x, double *y, double *a,double xs, double ys,double e){
	
	int i,j;
	double r;
	e=0.0;
	
	printf("��ϵ�Ϊ: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", x[i]); 
	}
	printf("\n");
	
	printf("��ϵ㺯��ֵΪ: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", y[i]); 
	}
	printf("\n");
	
		a[0]=2.20128;
	a[1]=2.54703;
	a[2]=-1.33325;
	a[3]=-0.516217;
	a[4]=0.297549;
	printf("��ϵ㺯��Ϊ: \n"); 
	printf("%+.7lf %+.7lf x %+.7lf x^2 %+.8lf x^3 %+.8lf x^4\n",a[0],a[1],a[2],a[3],a[4]);
	
	

	for(i=0;i<n;i++){
		r=0;
		for(j=0;j<m;j++){
			r+=a[j]*pow(x[i],j);
		}
		e+=pow(r-y[i],2);
	}
	
	e = sqrt(e);
	printf("���Ϊ: %lf\n", e);
	
	//printf("�����Ϊ: %f\n", xs);
	//printf("�������Ϻ���ֵΪ: %f\n", ys);
	
	return;
}

//���ֵ���� 
double compute_value(int m, double *a, double xs){
	int i;
	double ys=0.0;
	
	for(i=0;i<m;i++){
		ys+=a[i]*pow(xs,i);
	}
	
	return ys;
} 

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
