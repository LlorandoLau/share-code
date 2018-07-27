#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <dirent.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include "jpeglib.h"

extern JSAMPLE * image_buffer;	/* Points to large array of R,G,B-order data */
extern int image_height;	/* Number of rows in image */
extern int image_width;		/* Number of columns in image */

#define WIDTH 800
#define HEIGHT 480

void show_bmp_file(char *bmp_path);
GLOBAL(int)	show_JPEG_file (char * filename);
int inZone(int x,int y);
void changePre();
void changeNext();
int showPic(int index);
void readPicList(char* dirPath);
int is_File(char* s1,const char* s2);
void clear_screem();

void LastSong();
void nextSong();
void stopMusic();
void playMusic();
int musicPos(int,int);
void readMusicList(char*);

int is_File(char* s1,const char* s2)
{
	if(strstr(s1,s2)!=NULL)
		return 1;
	return 0;
}

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
typedef struct my_error_mgr* my_error_ptr;


METHODDEF(void) my_error_exit (j_common_ptr cinfo);

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

struct pic{
	char path[20];
	int file_type;
	//0: bmp
	//1:jepg
};


int lcd_fd;
int* lcd;

struct pic filePic[100];
int pic_index=0;
int sum_pic=0;

char* music[100];
int music_index=0;
int sum_music=0;
pthread_t music_Pid;
struct input_event ts;