#include<stdio.h>
int main()
{
	float x,y,z;
	printf("请输入坐标：(");
	scanf("%f,%f",&x,&y);
	printf(")\n");
	if((x-2)*(x-2)+(y-2)*(y-2) <= 1) z=10;
	else if((x+2)*(x+2)+(y-2)*(y-2) <= 1) z=10;
	else if((x-2)*(x-2)+(y+2)*(y+2) <= 1) z=10;
	else if((x+2)*(x+2)+(y+2)*(y+2) <= 1) z=10;
	else z=0;
	printf("高度是 %2.2f",z);
	return 0;
	
 } 
