#include<stdio.h>
int main()
{
	float b,l=0,m;
	int t,i;
	printf("���ı�����\n");
	scanf("%f",&b);
	printf("�����ڴ���5�ִ�ʽ\n"); 
	printf("��1��һ���Դ�5����\n"); 
	printf("��2���ȴ�2���ڣ����ں󽫱�Ϣ�ٴ�3����\n"); 
	printf("��3���ȴ�3���ڣ����ں󽫱�Ϣ�ٴ�2����\n"); 
	printf("��4����1���ڣ����ں󽫱�Ϣ�ٴ�1���ڣ�������5��\n"); 
	printf("��5������ڴ�������Ϣÿһ���Ƚ���һ��\n"); 
	printf("��ѡ����һ�֣���������Ӧ���֣����ǻ���������5���ı�Ϣ\n");
	scanf("%d",&t);
	switch(t)
	{
		case 1: l=b*0.03*5;   b=b+l;                       break;
		case 2: l=b*0.021*2;  b=b+l; l=b*0.0275*3; b=b+l;  break;
		case 3: l=b*0.0275*3; b=b+l; l=b*0.021*2;  b=b+l;  break;
		case 4: for(i=1;i<=5;i++) { l=b*0.015; b=l+b; }    break;
		case 5: for(i=1;i<=20;i++){ l=b*0.0035; b=l+b; }   break;
	}
	printf("���ı�Ϣ�� %f ",b);
	
	
	
	
	 
}
