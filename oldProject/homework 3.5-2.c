#include<stdio.h>
int main()
{
	float b,l=0,m;
	int t,i;
	printf("您的本金是\n");
	scanf("%f",&b);
	printf("五年期存款共有5种存款方式\n"); 
	printf("（1）一次性存5年期\n"); 
	printf("（2）先存2年期，到期后将本息再存3年期\n"); 
	printf("（3）先存3年期，到期后将本息再存2年期\n"); 
	printf("（4）存1年期，到期后将本息再存1年期，连续存5次\n"); 
	printf("（5）存活期存款，活期利息每一季度结算一次\n"); 
	printf("您选择哪一种，请输入相应数字，我们会给您计算出5年后的本息\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1: l=b*0.03*5;   b=b+l;                       break;
		case 2: l=b*0.021*2;  b=b+l; l=b*0.0275*3; b=b+l;  break;
		case 3: l=b*0.0275*3; b=b+l; l=b*0.021*2;  b=b+l;  break;
		case 4: for(i=1;i<=5;i++) { l=b*0.015; b=l+b; }    break;
		case 5: for(i=1;i<=20;i++){ l=b*0.0035; b=l+b; }   break;
	}
	printf("您的本息是 %f ",b);
	
	
	
	
	 
}
