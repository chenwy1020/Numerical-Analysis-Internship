#include <stdio.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////////////
//   2020-05-12
//  ������������ʾ�Ӵ���ͼ����Ϣ�������ļ� a.txt �ж�ȡ���ݣ� 
//   ���ֱ�����Ļ�ϵ���EGE�⺯����ͼ�� 
//   �Լ���ͼ��Ҷ���Ϣ ת���� ASC�ַ� ������ļ� aout.txt�У���ʵ���ַ���ʽ�鿴ͼ��
// 
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//
// ����ı�������������� ����EGEͼ���Ĺ��� 
// -lgraphics -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid -mwindows
// 
// �����Ҫ��������̨���ںͻ�ͼ���ڹ���Ļ���ȥ�������е� -mwindows ��
//  -lgraphics -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid 
//   ������ -mconsole �滻 -mwindows
// 
///////////////////////////////////////////////////////////////////////////////////////
#include <graphics.h>

#define COL  150
#define ROW  60
int main()
{ 
	int imgc[ROW][COL]; // 60��150�еĶ�ά���飬���ڱ���ͼ������
	int width,high; 
	char lib[]="@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`\'. "; //����Ҷ���Ϣ���ַ����� 
	int level=100;
 
	int maxX,maxY;
	FILE *fp,*fpout;  //file pointer
	
	if((fp=fopen("a.txt","r"))==NULL) // open data file a.txt
	{
		printf("\nError! Can't find file a.txt.\n");
		exit(0); // if Failure then exit
	} 

	if((fpout=fopen("aout.txt","w"))==NULL) // open data file aout.txt
	{
		printf("\nError! Can't find file aout.txt.\n");
		exit(0); // if Failure then exit
	} 

	level=strlen(lib);//�õ��ַ�����ĳߴ� ��Ҳ�����ַ�ͼ��Ļҽף����е���ɫ�������� 
	
	// �ļ� a.txt �ﱣ����� �� Ϊ150 �߶�Ϊ60 ��ͼ��ĻҶ���Ϣ ��ÿ����������һ�����ص�ĻҶ�ֵ�� 
	//if success  load data from a.txt into the dim imgc
	// and write data to aout.txt  in char mode
	for(high=0;high<ROW;high++)
	{
		for(width=0;width<COL; width++)
		{
			fscanf(fp,"%d ", &imgc[high][width]);
			
			fprintf(fpout,"%c", lib[(int)(level*imgc[high][width]/256.0)]);
		}
		fprintf(fpout,"\n");
	}


	fclose(fp); //close file a.txt
	fclose(fpout); //close file aout.txt
		
	// �ַ�ͼ���ļ�aout.txt�ɹ������� ���ü��±����ı��鿴���ߴ� aout.txt��
	// ���ò鿴�������ֺ�Ϊ�� ���塢���桢С�� ���������ò鿴�ĸ�ʽΪ���Զ����У�	
	//�������ܿ���������aout.txt�е��ַ������ɵ�ͼ��
	
    /*����ͼ��ģʽ*/
//	initgraph(1024,768,1); //EasyX
    initgraph(640, 480,0); //EGE
    
    maxX = getmaxx(); /*�õ���ǰģʽ�µ���Ļˮƽ�ֱ���*/
    maxY = getmaxy(); /*�õ���ǰģʽ�µ���Ļ��ֱ�ֱ���*/
    printf("%d %d\n",maxX,maxY);
    
	//draw the picture on the screen
	for(high=0;high<ROW;high++)
		for(width=0;width<COL; width++)
		{
	      //�Ի��� �ķ�ʽ��Сͼ 
		  putpixel(width,high,RGB(imgc[high][width],imgc[high][width],imgc[high][width]));
		 
		 //�� ��ʵ��Բ�ķ�ʽ���õ�ǰ�Ҷ���Ϣ����ͼ 
		   setcolor(RGB(imgc[high][width],imgc[high][width],imgc[high][width]));
		   circle(width*4,high*4,4);
		}

    getch();
    closegraph();  /* �˳�����ǰ��Ҫ�ر�ͼ��ģʽ */
	
	return 0;

}
