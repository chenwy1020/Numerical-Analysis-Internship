#include<stdio.h>
int main()
{
	float x,y,z;
	printf("���������꣺(   ,    )\b\b\b\b\b\b\b");
	scanf("%f,%f",&x,&y);
	if((x-2)*(x-2)+(y-2)*(y-2) <= 1) z=10;
	else if((x+2)*(x+2)+(y-2)*(y-2) <= 1) z=10;
	else if((x-2)*(x-2)+(y+2)*(y+2) <= 1) z=10;
	else if((x+2)*(x+2)+(y+2)*(y+2) <= 1) z=10;
	else z=0;
	printf("�߶��� %2.2f",z);
	return 0;
	
 } 
