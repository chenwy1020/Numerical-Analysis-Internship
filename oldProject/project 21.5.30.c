#include<stdio.h>
#include<string.h>
void move(char x[], int n, int m)
{
	char b[n];
	int i;
	for(i=0;i<n-m;i++)
		b[i+m]=x[i];
	for(i=n-m;i<n;i++)
		b[i-n+m]=x[i];
	for(i=0;i<n;i++)
		x[i]=b[i];

}

int main()
{
	int n,m,i;
	printf("请输入个数和移动位数：\n");
	scanf("%d %d",&n,&m);
	getchar();
	char a[n];
	for(i=0;i<n;i++)
		scanf("%c",&a[i]);
	move(a, n, m);
	for(i=0;i<n;i++)
		printf("%c",a[i]);

	return 0;
}









