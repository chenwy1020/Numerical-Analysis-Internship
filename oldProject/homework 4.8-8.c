#include<stdio.h>
int main()
{
	int s,t,l;
	printf("请输入成绩：\n");
	scanf("%d",&s);
	t=s/10;
	switch(t)
	{
		case 1 : 
		case 2 :
		case 3 :
		case 4 :
		case 5 : l='E'; break;
		case 6 : l='D'; break;
		case 7 : l='C'; break;
		case 8 : l='B'; break;
		case 9 : 
		case 10: l='A'; break;		
	}
	printf("您的成绩是 %c",l);
	return 0;
}
