//编程：某班有50个学生，三门课。分别编写3个函数实现以下要求：  
//假定：学号由6位数字组成；姓名不超过10个字符；每门课的成绩采用百分制，可以是小数，单科成绩小于60分为不及格。
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
//（1） 函数一：求班级各门课的平均分； 
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
//（2） 函数二：找出有两门以上不及格的学生，并输出其学号和不及格课程的成绩
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
//（3） 函数三：找出三门课平均成绩在85-90分的学生，并输出其学号和姓名  
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
//另外，要求定义适当的结构体数据类型用于描述学生的学号、姓名、三门课的成绩等个人信息，
//并编写完整主程序以实现输入50个学生的学号、姓名和各科成绩，然后调用上述函数输出结果。
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


