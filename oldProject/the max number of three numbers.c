#include<stdio.h>
int main() 
	{   
		int max(int x,int y,int z);
		int a,b,c,e;
		printf("请输入三个参数:\n");
		scanf("%d %d %d",&a,&b,&c);
		e=max(a,b,c);
		printf("最大值为：\n%d ",e);
		getchar();
		getchar(); 
        return 0;
 	} 
int max(int x,int y,int z)
	{
 		int q,w;
 		if(x>y) q=x;
		else q=y;
 		if(q>z)w=q;
 		else w=z;
 		return(w);
	}
