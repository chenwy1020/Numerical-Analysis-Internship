#include<stdio.h>
//��ת���ķǸ�������Ҫ����������Ӽ�������
//���м���ת������Ļ����Ĺ���ģ����һ���ݹ麯����ʵ�� 
struct stu
{
	int a[2];
	short b;
	char c[2];
};

int main()
{
	struct stu a;
	printf("%d",sizeof(a));
} 

