//��̣�ĳ����50��ѧ�������ſΡ��ֱ��д3������ʵ������Ҫ��  
//�ٶ���ѧ����6λ������ɣ�����������10���ַ���ÿ�ſεĳɼ����ðٷ��ƣ�������С�������Ƴɼ�С��60��Ϊ������
#include<stdio.h>
#include<stdlib.h>
struct Student
{
	int num;
	char name[10];
	float score1;
	float score2;
	float score3;
}Students[50];
typedef struct Student Student;
//��1�� ����һ����༶���ſε�ƽ���֣� 
float *Average(Student p[])
{
	float *average,p1=0,p2=0,p3=0;
	average=(float*)malloc(sizeof(float));
	int i;
	for(i=0;i<50;i++)
	{
		p1 += p[i].score1;
		p2 += p[i].score2;
		p3 += p[i].score3;
	}
	average[0]=p1/50.0;
	average[1]=p2/50.0;
	average[2]=p3/50.0;
	return(average);
}
//��2�� ���������ҳ����������ϲ������ѧ�����������ѧ�źͲ�����γ̵ĳɼ�
void FindBad(Student p[])
{
	int i;
	for(i=0;i<50;i++)
	{
		if(p[i].score1<60&&p[i].score2<60&&p[i].score3<60)
			printf("num=%d score1=%.2f score2=%.2f score3=%.2f\n",p[i].num,p[i].score1,p[i].score2,p[i].score3);
		else if(p[i].score1<60&&p[i].score2<60)
			printf("num=%d score1=%.2f score2=%.2f\n",p[i].num,p[i].score1,p[i].score2);		
		else if(p[i].score1<60&&p[i].score3<60)
			printf("num=%d score1=%.2f score3=%.2f\n",p[i].num,p[i].score1,p[i].score3);		
		else if(p[i].score2<60&&p[i].score3<60)
			printf("num=%d score2=%.2f score3=%.2f\n",p[i].num,p[i].score2,p[i].score3);
	}
	
}
//��3�� ���������ҳ����ſ�ƽ���ɼ���85-90�ֵ�ѧ�����������ѧ�ź�����  
void FindGood(Student p[])
{
	float a_s[50];
	int i;
	for(i=0;i<50;i++)
		a_s[i]=(p[i].score1+p[i].score2+p[i].score3)/3.0;
	for(i=0;i<50;i++)
		if(a_s[i]<=90&&a_s[i]>=85)
		printf("num=%d name=%s\n",p[i].num,p[i].name);
}
//���⣬Ҫ�����ʵ��Ľṹ������������������ѧ����ѧ�š����������ſεĳɼ��ȸ�����Ϣ��
//����д������������ʵ������50��ѧ����ѧ�š������͸��Ƴɼ���Ȼ���������������������
int main()
{
	int i,j;
	char c;
	float *p;
	for(i=0;i<50;i++)
	{
		c=getchar();
		for(j=0;(c=getchar())!='\0'&&j<10;j++)
			scanf("%c",Students[i].name+j);
		scanf("%d%f%f%f",&Students[i].num,&Students[i].score1,&Students[i].score2,&Students[i].score3);
	}
	p=Average(Students);
	for(i=0;i<3;i++)
	  printf("score%d = %.2f\n",i,p[i]);
	printf("\n");
	FindBad(Students);
	printf("\n");	
	FindGood(Students);
}


