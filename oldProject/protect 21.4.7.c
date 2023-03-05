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
	getch();//键盘输入后立即反应，使得程序暂停一下 ，且不回显
	getche();//键盘输入后立即反应，且回显
	getchar();//键盘输入后还需回车键 才能转入内存，且回显 
	 
	
	
	

	
}

