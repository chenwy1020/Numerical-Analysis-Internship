#include<stdio.h>
void main()
{
	char c;
	c=getchar();
	putchar(c);
	putchar('\n');
	printf("%c\n",c);
	printf("%d\n",c);
	system("pause");
	
	
	
	int x=0,y;
	y=x++;
	printf("y=%d\n x=%d",y,x);
	system("pause");
	
	char a='Z';
	putchar(a);	
	putchar('\101');
	putchar('\n');
	putchar('B');
	putchar('\'');
	system("pause");
	
	
	
	char c1,c2,ch;
	printf("Please input chars:");
	c1=getchar();
	while(ch=getchar() != '\n') ;
	c2=getchar();
	printf("\nc1:%c,c2:%c\n",c1,c2);
	printf("END");
	
	unsigned long i=1,p=1;
	do{
		p*=i;
		i++;
	}while(i<=5);
	printf("\n The result is:%d",p);
	getch();//���������������Ӧ��ʹ�ó�����ͣһ�� ���Ҳ�����
	getche();//���������������Ӧ���һ���
	getchar();//�����������س��� ����ת���ڴ棬�һ��� 
	 
	
	
	

	
}

