#include<stdio.h>
int main()
{
	float A[7][7],b[7],k,t,x[7];
	int i,j,m,n;
	printf("请按行输入增广矩阵（A b）的信息：\n");
	for(i=0;i<=6;i++)
		for(j=0;j<=7;j++)
		{
			if(j<=6) scanf("%f",&A[i][j]);
			else scanf("%f",&b[i]);
		}	
	for(i=0;i<=6;i++)
		for(j=0;j<=7;j++)
		{
			if(j<=6) printf("%.2f\t",A[i][j]);
			else printf("%.2f\n",b[i]);
		}
	for(m=0;m<=6;m++)
	{
		if(A[m][m]==0)
		{
			for(n=m;n<=6;n++)
			{
				if(A[n][m]==0)continue;
				else 
				{
					for(j=m;j<=7;j++)
					{
						if(j<=6) 
						{
							t=A[m][j];
							A[m][j]=A[n][j];
							A[n][j]=t;
						}
						else b[m]=b[n];
					}
				}
			}
		}
		if(A[m][m]==0)continue;
		for(i=0;i<=6;i++)
		{
			if(i==m)continue;
			k=A[i][m]/A[m][m];
			for(j=m;j<=7;j++)
			{
				if(j<=6)A[i][j]=A[i][j]-A[m][j]*k;
				else b[i]=b[i]-b[m]*k;
			}
		}
	}
	for(i=0;i<=6;i++)
		for(j=0;j<=7;j++)
		{
			if(j<=6) printf("%.2f\t",A[i][j]);
			else printf("%.2f\n",b[i]);
		}
	printf("方程的解为:");
	for(j=0;j<=6;j++) 
	{
		if(A[j][j]!=0)
		{
			x[j]=b[j]/A[j][j];
			printf("%.2f\t",x[j]);
		}
		else if(A[j][j]==0&&b[j]==0) printf("x%d\t",j);
		else if(A[j][j]==0&&b[j]!=0) printf("无解"); 
	}
	
	
 } 

