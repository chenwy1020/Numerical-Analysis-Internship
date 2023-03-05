 #include <stdio.h>
#include <stdlib.h>
#include <math.h>

void least_square(int n, double *x, double *y, int m, double *a);//��С���˷�
void assemble_matrix(int n, double *x, int m, double **A);//��ȡ���� 
void right_side(int n, double *x, double *y, int m, double *b);//��ȡ�Ҳ����� 
void basis_function(int n, double *x, int i, double *phi_i);//���ɻ������� 
double dot(int n, double *vector1, double *vector2);//�����ڻ� 
void output(int n, int m,double *x, double *y, double *a); //���  ��ϵ� ��ϵ㺯��ֵ ��ϵ㺯�� ���
double compute_value(int n, double *a, double xs);//���ֵ���� 
void uniform_partition(int m, double left, double right, double *xs);//�������� 
double f(double x);//������ϵ㺯��ֵ 
void ColElim(int n, double **A, double *b, double *x);//����Ԫ��ȥ���������Է��� 


int main(){
	/*
	�ó�������������С���˷��������ƽ���ƽ�����ʽ
	
	x ��ʾ��ϵ�����
	y ��ʾ��ϵ㺯��ֵ
	a ��ʾ������Ķ���ʽϵ��
	n ��ʾ��ϵ����
	m ��ʾ���������� 
	xs ��ʾ����� 
	ys ��ʾ�������Ϻ���ֵ 
	*/
	int n=11,m=5;
	int i;
	 
	double left = -1.0, right = 1.0;
	
	double x[n];
	double y[n];
	
	double *a;
	
	//������ϵ�������ڴ� 
	a = (double *)malloc(sizeof(double)*m);
	
	
	uniform_partition(n-1,left,right,x);
	for(i=0;i<n;i++){
		y[i]=f(x[i]);
	}
	
	
	//������С���˷�����ϵ��a 
	least_square(n, x, y, m, a);
	
	//��������� 
	output(n, m, x, y, a);
	
	//�ͷ��ڴ� 
	free(a); 
	
	return 0;
}

//��С���˷� 
void least_square(int n, double *x, double *y, int m, double *a){
	int i,j; 
	double **A;
	double b[m];
	
	//��ʼ�� A b 
	A = (double **)malloc(sizeof(double *)*(m));
	for(i=0; i<m; i++ ){
		A[i] = (double*)malloc(sizeof(double)*(m));
	}

	assemble_matrix(n,x,m,A);

	right_side(n,x,y,m,b);

	ColElim(m,A,b,a);
	
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
	if(i<=2){
		for(k=0;k<n;k++){
			phi_i[k]=pow(x[k],i);
		}
	}
	if(i==3){
		for(k=0;k<n;k++){
			phi_i[k]=sin(2*x[k]);
		}		
	}
	if(i==4){
		for(k=0;k<n;k++){
			phi_i[k]=cos(2*x[k]);
		}		
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

//���  ��ϵ� ��ϵ㺯��ֵ ��ϵ㺯�� ���
void output(int n,int m, double *x, double *y, double *a){
	
	int i;
	double e=0,r;
	
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
	
	printf("��ϵ㺯��Ϊ: \n"); 
	printf("%+lf %+lf x %+lf x^2 %+lf sin(2x) %+lf cos(2x)\n",a[0],a[1],a[2],a[3],a[4]);
	
	for(i=0;i<n;i++){
		r=0;
		r=a[0]+a[1]*x[i]+a[2]*pow(x[i],2)+a[3]*sin(2*x[i])+a[4]*cos(2*x[i]);
		e+=pow(r-y[i],2);
	}
	
	e=sqrt(e);
	printf("���Ϊ: \n%lf\n", e);
	
	return;
}

//�������� 
void uniform_partition(int n, double left, double right, double *xs){
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
	h = (right-left) / n;
	
	//ÿ���ʷֵ����꼴Ϊ��˵�+����*���� 
	for(i=0;i<n+1;i++){
		xs[i] = left + h*i;
	}
	
}

double f(double x){

	double y; 
	
	y = exp(x*x+x);
	
	return y;
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
