#include<stdio.h>
#include<stdlib.h>
struct Student
{
	char *name;
	int age;
	float height;
	float weight;
	struct Student *p;
}x[10],*head,*new,*current,*new2,*market;

struct Student x1;
x1.age=18;

int main()
{
// 	分配空间 
	new=(struct Student*)malloc(sizeof(x[0]));
	new2=(struct Student*)malloc(sizeof(x[0]));
	current=(struct Student*)malloc(sizeof(x[0]));
	=(struct Student*)malloc(sizeof(x[0]));
// 创建链表 
	int i;
	head=x;
	for(i=0;i<10;i++)
	{
		if(i=9)
		{
			x[9].p=NULL;
			break;
		}	
		x[i].p = &x[i+1];
	}
// 
	new.p=head;
	head=new;
//
	
// 在链表尾部加入结点 new 
	current=head;			//通过current找到链表尾部 
	while(current->p!=NULL)
		current=current->p;
	current->p=new2;
	new2->p=NULL; 

	
	
	
	x[0].name = "陈文宇";
	x[0].age = 21;
	x[0].height = 1.73;
	x[0].weight = 68.5;
	
	x[1]=x[0];
	printf("%s %d %f %f\n",x[1].name, x[1].age, x[1].height, x[1].weight);

	
}
 
