 #include <stdio.h>
#include <stdlib.h>
#include <math.h>

void least_square(int n, double *x, double *y, int m, double *a);//最小二乘法
void assemble_matrix(int n, double *x, int m, double **A);//获取矩阵 
void right_side(int n, double *x, double *y, int m, double *b);//获取右侧向量 
void basis_function(int n, double *x, int i, double *phi_i);//生成基础向量 
double dot(int n, double *vector1, double *vector2);//计算内积 
void output(int n, int m,double *x, double *y, double *a); //输出  拟合点 拟合点函数值 拟合点函数 误差
double compute_value(int n, double *a, double xs);//拟合值计算 
void uniform_partition(int m, double left, double right, double *xs);//构建网格 
double f(double x);//计算拟合点函数值 
void ColElim(int n, double **A, double *b, double *x);//列主元消去法计算线性方程 


int main(){
	/*
	该程序用于利用最小二乘法计算最佳平方逼近多项式
	
	x 表示拟合点坐标
	y 表示拟合点函数值
	a 表示计算出的多项式系数
	n 表示拟合点个数
	m 表示基函数个数 
	xs 表示待求点 
	ys 表示待求点拟合函数值 
	*/
	int n=11,m=5;
	int i;
	 
	double left = -1.0, right = 1.0;
	
	double x[n];
	double y[n];
	
	double *a;
	
	//基函数系数申请内存 
	a = (double *)malloc(sizeof(double)*m);
	
	
	uniform_partition(n-1,left,right,x);
	for(i=0;i<n;i++){
		y[i]=f(x[i]);
	}
	
	
	//利用最小二乘法计算系数a 
	least_square(n, x, y, m, a);
	
	//输出计算结果 
	output(n, m, x, y, a);
	
	//释放内存 
	free(a); 
	
	return 0;
}

//最小二乘法 
void least_square(int n, double *x, double *y, int m, double *a){
	int i,j; 
	double **A;
	double b[m];
	
	//初始化 A b 
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

//获取矩阵 
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

//获取右侧向量 
void right_side(int n, double *x, double *y, int m, double *b){
	int i;
	double psi[n];
	
	for(i=0;i<m;i++){
		basis_function(n,x,i,psi);
		b[i]=dot(n,y,psi);
	}
}
 
//生成基础向量 
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

//计算内积 
double dot(int n, double *vector1, double *vector2){
	int i;
	double temp=0.0;
	
	for(i=0;i<n;i++){
		temp+=vector1[i]*vector2[i];
	}
	
	return temp;
	
} 

//输出  拟合点 拟合点函数值 拟合点函数 误差
void output(int n,int m, double *x, double *y, double *a){
	
	int i;
	double e=0,r;
	
	printf("拟合点为: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", x[i]); 
	}
	printf("\n");
	
	printf("拟合点函数值为: \n"); 
	for(i=0; i<n; i++){
		printf("%f ", y[i]); 
	}
	printf("\n");
	
	printf("拟合点函数为: \n"); 
	printf("%+lf %+lf x %+lf x^2 %+lf sin(2x) %+lf cos(2x)\n",a[0],a[1],a[2],a[3],a[4]);
	
	for(i=0;i<n;i++){
		r=0;
		r=a[0]+a[1]*x[i]+a[2]*pow(x[i],2)+a[3]*sin(2*x[i])+a[4]*cos(2*x[i]);
		e+=pow(r-y[i],2);
	}
	
	e=sqrt(e);
	printf("误差为: \n%lf\n", e);
	
	return;
}

//构建网格 
void uniform_partition(int n, double left, double right, double *xs){
	/*
	该程序用于对区间进行均匀剖分, 所得剖分点包括两个端点 
	
	m 表示剖分点个数 
	left 表示区间左端点
	right 表示区间右端点
	xs 表示剖分点坐标 
	*/	
	int i;
	double h;  
	
	//h表示剖分步长 
	h = (right-left) / n;
	
	//每个剖分点坐标即为左端点+步长*个数 
	for(i=0;i<n+1;i++){
		xs[i] = left + h*i;
	}
	
}

double f(double x){

	double y; 
	
	y = exp(x*x+x);
	
	return y;
}

//列主元消去法计算线性方程 
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
       	}   // 选列主元
       	if(r!=k){
          	for(i=k; i<n; i++){
             	ki = k*n+i;
             	ri = r*n+i;             
             	t = A[k][i];
             	A[k][i] = A[r][i];
             	A[r][i] = t;
          	} // 交换矩阵 A 的 r,k 两行元素
          	t = b[k];
          	b[k] = b[r];
          	b[r] = t;  // 交换 b 的 r,k 两行元素 
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
