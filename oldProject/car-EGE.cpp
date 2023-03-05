#include <stdio.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////////////
//   2020-05-12
//  本例程用于演示从存有图像信息的数据文件 a.txt 中读取数据， 
//   并分别在屏幕上调用EGE库函数绘图， 
//   以及将图像灰度信息 转化成 ASC字符 输出到文件 aout.txt中，以实现字符方式查看图像
// 
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//
// 下面的编译参数用于配置 基于EGE图像库的工程 
// -lgraphics -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid -mwindows
// 
// 如果想要保留控制台窗口和画图窗口共存的话，去掉参数中的 -mwindows 项
//  -lgraphics -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid 
//   或者用 -mconsole 替换 -mwindows
// 
///////////////////////////////////////////////////////////////////////////////////////
#include <graphics.h>

#define COL  150
#define ROW  60
int main()
{ 
	int imgc[ROW][COL]; // 60行150列的二维数组，用于保存图像数据
	int width,high; 
	char lib[]="@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`\'. "; //代替灰度信息的字符数组 
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

	level=strlen(lib);//得到字符数组的尺寸 ，也代表字符图像的灰阶（库中的颜色数量）。 
	
	// 文件 a.txt 里保存的是 宽 为150 高度为60 的图像的灰度信息 （每个整数代表一个像素点的灰度值） 
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
		
	// 字符图像文件aout.txt成功创建， 请用记事本等文本查看工具打开 aout.txt，
	// 设置查看的字体字号为： 宋体、常规、小六 ，并且设置查看的格式为不自动换行，	
	//这样就能看到保存在aout.txt中的字符所构成的图像
	
    /*启动图形模式*/
//	initgraph(1024,768,1); //EasyX
    initgraph(640, 480,0); //EGE
    
    maxX = getmaxx(); /*得到当前模式下的屏幕水平分辨率*/
    maxY = getmaxy(); /*得到当前模式下的屏幕竖直分辨率*/
    printf("%d %d\n",maxX,maxY);
    
	//draw the picture on the screen
	for(high=0;high<ROW;high++)
		for(width=0;width<COL; width++)
		{
	      //以画点 的方式画小图 
		  putpixel(width,high,RGB(imgc[high][width],imgc[high][width],imgc[high][width]));
		 
		 //以 画实心圆的方式，用当前灰度信息画大图 
		   setcolor(RGB(imgc[high][width],imgc[high][width],imgc[high][width]));
		   circle(width*4,high*4,4);
		}

    getch();
    closegraph();  /* 退出程序前需要关闭图形模式 */
	
	return 0;

}
