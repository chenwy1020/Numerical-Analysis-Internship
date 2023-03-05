#include<string.h>
#include<stdio.h>
#include<math.h>

int turn(char *x,int m)
{
	int y=0,i;
	for(i=0;i<=m;i++)
		y=y+((int)(x[i])-48)*pow(10,m-i);
	return(y);
}

int find(char *x, int *y,int *len)
{
	int a[50];
	char b[50];
	int i,j,n=0,m,q;
	for(i=0;x[i]!='\0';i++)
	{
		if(x[i]>='0'&&x[i]<='9')
		{
			for(j=0;x[i+j]>='0'&&x[i+j]<='9';j++)
				if(x[i+j+1]<'0'||x[i+j+1]>'9') n++;
				
			for(m=0;m<j;m++) b[m]=x[i+m];
			a[n-1]=turn(b,m);	
			i=i+j-1;
		}
	}

	*len = n;
	for(i=0;i<n;i++)
		*(y+i)=a[i];
	
}

int main()
{
	char str[50]={'\0'};
	gets(str);
	
	int num[50],len,i;
	find(str,num,&len);
	
	printf("所含整数有 %d 个",len);
	for(i=0;i<len;i++)
		printf("%d   ",num[i]);

}























