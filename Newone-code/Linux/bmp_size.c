#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
typedef struct tagBITMAPFILEHEADER
{
    short bfType;//位图文件的类型，必须为BM(1-2字节）
    int bfSize;//位图文件的大小，以字节为单位（3-6字节，低位在前）
    short bfReserved1;//位图文件保留字，必须为0(7-8字节）
    short bfReserved2;//位图文件保留字，必须为0(9-10字节）
    int bfOffBits;//位图数据的起始位置，以相对于位图（11-14字节，低位在前）
    //文件头的偏移量表示，以字节为单位
}__attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	int biSize;//本结构所占用字节数（15-18字节）
	int biWidth;//位图的宽度，以像素为单位（19-22字节）
	int biHeight;//位图的高度，以像素为单位（23-26字节）
	short biPlanes;//目标设备的级别，必须为1(27-28字节）
	short biBitCount;//每个像素所需的位数，必须是1（双色），（29-30字节）
	//4(16色），8(256色）16(高彩色)或24（真彩色）之一
	int biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
	//1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
	int biSizeImage;//位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
	int biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
	int biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
	int biClrUsed;//位图实际使用的颜色表中的颜色数（47-50字节）
	int biClrImportant;//位图显示过程中重要的颜色数（51-54字节）
}__attribute__((packed)) BITMAPINFOHEADER;

int main()
{

	BITMAPFILEHEADER  fil;//14字节 文件头
	BITMAPINFOHEADER  inf;//40字节 位图信息头
	
	//打开图片
	int bmp_fd = open("1.bmp",O_RDWR);
	if(bmp_fd < 0)
	{
		printf("open bmp error!\n");
	}
	
	//读取14个字节的文件头信息
	read(bmp_fd,&fil,sizeof(fil));
	//读取40个字节的位图信息头信息
	read(bmp_fd,&inf,sizeof(inf));
	
	printf("bmp Width = %d\n",inf.biWidth);
	printf("bmp Height = %d\n",inf.biHeight);
	
	
	//读取1152000个字节的像素数据
	//read(bmp_fd,bmp_buf,sizeof(bmp_buf));
	
	//关闭图片
	close(bmp_fd);

	return 0;
}