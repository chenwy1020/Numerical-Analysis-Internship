#include<stdio.h>
#include<math.h>

int main(){
	//�������� 
	void MatPrintf(double Q[],int m,int n);
	void GMRES(double A[],double x0[],double b[],double x[],int m,int n,double epsilon);
	void MatMul(double A[],double B[],double y[],int m,int n,int p);
	int n=4,i,m=4;
	double A[16]={13,9,9,11,9,11,6,9,9,6,12,7,11,9,7,10},b[4]={42,35,34,37};
	double x0[4]={0,0,0,0},x[4];
	double epsilon=0.000001;
	
	GMRES(A,x0,b,x,m,n,epsilon);
	printf("\nxm = \n");
	MatPrintf(x,n,1);
}

//GMRES�����㷨 
void GMRES(double A[],double x0[],double b[],double x[],int m,int n,double epsilon){
	//�������� 
	double InnerProduct(double A[],double B[],int n);				//�ڻ� 
	double Norm2(double A[],int n);					 				//2����
	void MatMul(double A[],double B[],double y[],int m,int n,int p);//����˷�
	void Givens(double A[],double Q[],double R[],double y[],int n);	//Given�任 
	void Givensij(double A[],double c,double s,int i,int j,int n);	//�� A ��i�к� j������Givens�任 
	void MatConVi(double V[],double vj[],int m,int n,int j);		//�̳� V�ĵ� j�� 
	void UpTriSys(double A[],double x[],double y[],int n);			//AΪ�����Ǿ������ Ax=y 
	void MatConvi(double V[],double vj[],int m,int n,int j);		//�� vj ������V�ĵ� j��
	void MatPrintf(double Q[],int m,int n);							//������� 
	
	int i,j,k;
	double V[n*m],H[(m+1)*m],tempb[m+1],CS[2*m];
	double w[n],v[n],h[m+1],xm[n];
	double t,p;
	double c,s;
	
	//��ʼ�� ������v1���� e1������H�� ��m+1�� 
	MatMul(A,x0,v,n,n,1);
	for(k=0;k<n;k++){
		v[k]=b[k]-v[k];
	}
	p=Norm2(v,n);
	for(k=0;k<n;k++){
		v[k]=v[k]/p;
		V[k*m]=v[k];
	}	
	
	printf("�� 0 ���в�Ϊ %lf\n",p);
	tempb[0]=p;
	
	for(j=1;j<=m;j++){
		
		/* GMRES�㷨 ���� H�� V */
		MatConVi(V,v,n,m,j);  //v�̳� V�ĵ� j��

		MatMul(A,v,w,n,n,1);//����wj = Avj
		
		for(i=1;i<=j;i++){
			MatConVi(V,v,n,m,i);
			t=InnerProduct(w,v,n);//�����ڻ� (w,v_j) 
			H[(i-1)*m+j-1]=t; 	  //��H_ij��ֵ 
			for(k=1;k<=n;k++){w[k-1]-=t*v[k-1];}//���� W		
		}
		
		t=Norm2(w,n);//���� w��2���� 
		H[j*m+j-1]=t;//H_(j+1)j ��ֵ 
		

		
		/*Givens�任��в�*/
		MatConVi(H,h,m+1,m,j);//h�̳� H�ĵ� j��
		for(i=1;i<=j-1;i++){
			Givensij(h,CS[i-1],CS[m+i-1],i,i+1,1);
		}	
		
		//���� c, s,����¼�� CS�����У� H_j+1,j  H_j,j 
		t=sqrt(h[j-1]*h[j-1]+h[j]*h[j]);
		c=h[j-1]/t;   s=h[j]/t; 
		CS[j-1]=c;    CS[m+j-1]=s;
		h[j-1]=t;     h[j]=0;

		//�����Ҷ�����
		Givensij(tempb,CS[j-1],CS[m+j-1],j,j+1,1);
		
		t=H[j*m+j-1];//���� H_j+1,j����Ϣ �����ڸ��� V�ĵ� j+1 �� 
		
		//���� H
		for(i=1;i<=j+1;i++){ 
			H[(i-1)*m+j-1]=h[i-1]; 
		} 
	
		//����в�
		p=tempb[j];
		printf("�� %d �Ĳв�Ϊ %lf\n",j,p);
		 
		if(fabs(p)<epsilon){
			break;
		}
		if(fabs(t)<epsilon){
			break;
		}
	
		//���� V�ĵ� j+1 �� 
		for(k=1;k<=n ;k++){ 
			V[(k-1)*m+j] = w[k-1]/t;
		}
		

	} 
	
	/*���������ϵͳ*/		
	//�� H ����� �����ǲ��� ��bj
	double R[j*j],bj[j],y[j];
	for(i=1;i<=j;i++){
		for(k=1;k<=j;k++)
			R[(i-1)*j+k-1]=H[(i-1)*m+k-1];
		bj[i-1]=tempb[i-1];
	}
	UpTriSys(R,y,bj,j);
	
	//���½�
	for(i=1;i<=n;i++){
		t=0;
		for(k=1;k<=j;k++){
			t+=V[(i-1)*m+k-1]*y[k-1];
		}
		x[i-1]=x0[i-1]+t;
	} 
	
	/*
	//�õ� Qm+1��ת�õõ�һ�е�ǰ m�� 
	for(i=1;i<=m;i++)
		b0[i-1]=Q[i-1]; 
	if(p<epsilon){
		UpTriSys(R,x,b0,m);
		MatMul(V,x,xm,n,m,1);
		for(i=1;i<=n;i++)xm[i]+=x0[i];
		//MatPrintf(xm,n,1);
		for(i=1;i<=n;i++){printf("%lf\n",xm[i-1]);}
	}
	*/
	
	
}
 
//Given�任
void Givens(double A[],double Q[],double R[],double y[],int n){
	//�������� 
	void MatT(double Q[],int n);
	void MatCon(double Q[],double z[],int n);
	
	int i,j,k;
	int p,q;
	double c,s,t;
	double A0[n*n];
	MatCon(A,A0,n*n);
	
	//Q�ĳ�ֵ 
	for(i=1;i<=n*n;i++)
		Q[i-1]=0;
	for(i=1;i<=n;i++)
		Q[(i-1)*(n+1)]=1;
	for(i=1;i<=n-1;i++) 
	{
		for(j=i+1;j<=n;j++)
		{
			//Step1: ����Givens �����������������Aii��Aji��ֵ�� 
			p=(i-1)*(n+1);
			q=(j-1)*n+i-1;
			c=A[p]/sqrt(A[p]*A[p]+A[q]*A[q]);
			s=A[q]/sqrt(A[p]*A[p]+A[q]*A[q]);
			A[p]=sqrt(A[p]*A[p]+A[q]*A[q]);
			A[q]=0;
			
			//Step2: ��A��i, j �е�����Ԫ�ؽ��б任�õ�����R
			for(k=i+1;k<=n;k++)
			{
				p=(i-1)*n+k-1;
				q=(j-1)*n+k-1;
				t=A[p];
				A[p]= c*t+s*A[q];
				A[q]=-s*t+c*A[q];
			}
			//Step3: ���Ҷ����i, j Ԫ�ؽ��б任
			t=y[i-1];
			y[i-1]= c*t+s*y[j-1];
			y[j-1]=-s*t+c*y[j-1];
			
			//t=e1[i-1];
			//e1[i-1]= c*t+s*e1[j-1];
			//e1[j-1]=-s*t+c*e1[j-1];
			
			//Step4: ���������� Q �ĵ�i, j ��Ԫ�ؽ��б任
			for(k=1;k<=n;k++)
			{
				p=(i-1)*n+k-1;
				q=(j-1)*n+k-1;
				t=Q[p];
				Q[p]= c*t+s*Q[q];
				Q[q]=-s*t+c*Q[q];
			}	
		}
	}
	//��Q��ת�� 
	MatT(Q,n);	
	MatCon(A,R,n*n);
	MatCon(A0,A,n*n);
}

//�� A ��i�к� j������Givens�任 
void Givensij(double A[],double c,double s,int i,int j,int n){
	int k;
	double p,q;
	for(k=1;k<=n;k++){
		p=c*A[(i-1)*n+k-1]+s*A[(j-1)*n+k-1];
		q=c*A[(j-1)*n+k-1]-s*A[(i-1)*n+k-1];
		//printf("p=%lf\n",p);
		//printf("q=%lf\n",q);
		A[(i-1)*n+k-1]=p;
		A[(j-1)*n+k-1]=q;
	}
}

//Householder�任
void Householder(double A[],double Q[],double R[],double y[],int n){
	//�������� 
	void MatPrintf(double Q[],int m,int n);
	void MatT(double Q[],int n);
	void MatCon(double Q[],double z[],int n);
	
	int i,j,k,i1,j1;
	double t,t1=0,t2=0,t3=0,v[n];
	double A0[n*n];
	MatCon(A,A0,n*n);
	//double P[n*n];
	
	//��ʼ�� 
	for(i1=1;i1<=n;i1++)
		for(j1=1;j1<=n;j1++)
		{
			Q[(i1-1)*n+j1-1]=0;
			Q[(i1-1)*(n+1)]=1; 
		}
	for(i=1;i<=n;i++)
		v[i-1]=0;		
		
	for(i=1;i<=n-1;i++)
	{
		/*
		//���õ�λ��������ɵ�househorder������Ϣ 
		for(i1=1;i1<=n;i1++)
			for(j1=1;j1<=n;j1++)
			{
				P[(i1-1)*n+j1-1]=0;
				P[(i1-1)*(n+1)]=1; 
			}	
		*/	
		
		//һ.����householder���� 

		t=0;
		for(k=i;k<=n;k++)
			t+=A[(k-1)*n+i-1]*A[(k-1)*n+i-1];
		t=sqrt(t);
		if(A[(i-1)*(n+1)]<0) t=-t;
		
	
		v[i-1]=A[(i-1)*(n+1)]+t;
		t1=v[i-1]*v[i-1];
		for(k=i+1;k<=n;k++)
		{
			v[k-1]=A[(k-1)*n+i-1];//����v = x + ��e1 ��  x + ��e1��2���� 
			t1+=v[k-1]*v[k-1];
		}
		t1=2/t1;
		
		
		//��Aת��Ϊ R ���ȶԵ�i�и�ֵ���ڶԺ�n-i�и��� 
		A[(i-1)*(n+1)]=-t;
		for(k=i+1;k<=n;k++)
			A[(k-1)*n+i-1]=0;
		for(j=i+1;j<=n;j++)
		{
			t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
			for(k=i;k<=n;k++)
				t2+=v[k-1]*A[(k-1)*n+j-1];
			t3=t1*t2;
			for(k=i;k<=n;k++)
				A[(k-1)*n+j-1]-=t3*v[k-1];
		} 
		
		//����y
		t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
		for(k=i;k<=n;k++)
			t2+=v[k-1]*y[k-1];
		t3=t1*t2;
		for(k=i;k<=n;k++)
			y[k-1]-=t3*v[k-1];
		
		//���� Q
		for(j=1;j<=n;j++)
		{
			t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
			for(k=i;k<=n;k++)
				t2+=v[k-1]*Q[(k-1)*n+j-1];
			t3=t1*t2;
			for(k=i;k<=n;k++)
				Q[(k-1)*n+j-1]-=t3*v[k-1];
		}
		MatT(Q,n); 	
		/* 
		//�õ�λ��������¼househorder�����ÿһ����Ϣ 
		for(j=1;j<=n;j++)
		{
			t2=0;  //��jÿ��ѭ����Ҫ��t2��ԭΪ0
			for(k=i;k<=n;k++)
				t2+=v[k-1]*P[(k-1)*n+j-1];
			t3=t1*t2;
			for(k=i;k<=n;k++)
				P[(k-1)*n+j-1]-=t3*v[k-1];
		}
		printf("H(%d) = \n",i-1);
		MatPrintf(P,n,n);
		*/
	}
	//���A->R��I->Q,y->y(new);
	MatCon(A,R,n*n);
	MatCon(A0,A,n*n);
	
}

//AΪ�����Ǿ������ Ax=y 
void UpTriSys(double A[],double x[],double y[],int n){
	int i,j,m;
	double p[n];
	for(j=0;j<n;j++)
		p[j]=y[j];
	for(j=n;j>=1;j--)
	{
		m=(j-1)*(n+1);
		x[j-1]=p[j-1]/A[m];
		for(i=j-1;i>=1;i--)
			p[i-1]=p[i-1]-A[(i-1)*n+j-1]*x[j-1];
	}
}

//����ת�� 
void MatT(double Q[],int n){
	double t;
	int p,q,i,j;
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
		{
			p=(i-1)*n+j-1;
			q=(j-1)*n+i-1;
			t=Q[p];
			Q[p]=Q[q];
			Q[q]=t;
		}
}

//�������
void MatPrintf(double Q[],int m,int n){
	int i,j;
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++){
			printf("%lf\t",Q[(i-1)*n+j-1]);
		}
		printf("\n");
	}
} 

//�ڻ� 
double InnerProduct(double A[],double B[],int n){
	double p=0;
	int i;
	for(i=0;i<n;i++){p+=A[i]*B[i];}
	return p;
}

//2���� 
double Norm2(double A[],int n){
	double p=0;
	int i;
	for(i=0;i<n;i++){p+=A[i]*A[i];}
	return sqrt(p);
}

//����̳�
void MatCon(double Q[],double z[],int n){
	int i;
	for(i=0;i<n;i++)
		z[i]=Q[i];
} 

//�̳� V�ĵ� j �� 
void MatConVi(double V[],double vj[],int m,int n,int j){
	int k;
	for(k=1;k<=m;k++){
		vj[k-1]=V[(k-1)*n+j-1];
	}
} 

//�� vj ������V�ĵ� j�� 
void MatConvi(double V[],double vj[],int m,int n,int j){
	int k;
	for(k=1;k<=m;k++){
		V[(k-1)*n+j-1]=vj[k-1];
	}	
}

//����˷�
void MatMul(double A[],double B[],double y[],int m,int n,int p){
	int i,j,k;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			y[(i-1)*p+j-1]=0;
	for(i=1;i<=m;i++)
		for(j=1;j<=p;j++)
			for(k=1;k<=n;k++)
				y[(i-1)*p+j-1]+=A[(i-1)*n+k-1]*B[(k-1)*p+j-1];
}
