#include "header.h"
int Sys_pic()
{
	show_component();
	while(1)
	{
		read(ts_fd,&ts,sizeof(ts));
		if(ts.type == EV_ABS && ts.code == ABS_X)
		{
			x = ts.value;
		}
		if(ts.type == EV_ABS && ts.code == ABS_Y)
		{
			y = ts.value;
		}
		if(ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
		{
			int pos=inZone(x,y);
			switch(pos)
			{
				case 1:	changeNext();	break;
				case 2:changePre();	break;
				case 3:
					clear_screen();
					return 0;
				default: break;
			}
		}
	}
	return 0;
}

int inZone(int x,int y){
	if(x>600 && y>280)	return 1;
	else if (x<200 && y>280)	return 2;
	else if(x>600 && y<200) return 3;
	else	return 0;
}

void changePre()
{
	if(pic_index==0)
		return ;
	printf("in cPre: %d %d\n",pic_index,sum_pic);
	pic_index--;
	showPic(pic_index);
}

void changeNext()
{
	if(pic_index==sum_pic-1)
		return ;
	printf("in cNext: %d %d\n",pic_index,sum_pic);
	pic_index++;
	showPic(pic_index);
}

int showPic(int pic_index)
{
	int type=filePic[pic_index].file_type;
	char* path=filePic[pic_index].path;
	printf("in showPic: %d %s\n",pic_index,path);
	switch(type)
	{
		case 0:
			show_bmp_file(path);
			break;
		case 1:
			show_JPEG_file(path);
			break;
		default:
			break;
	}
	return 0;
}

void show_component(){
	show_bmp_on_border("/pic/next.bmp",640,400); 
	show_bmp_on_border("/pic/pre.bmp",0,400);
	show_bmp_on_border("/pic/quit.bmp",640,0);
}


void show_bmp_on_border(char* bmp_path,int x_s,int y_s)
{
	BITMAPFILEHEADER  fil;//14字节 文件头
	BITMAPINFOHEADER  inf;
	
	int bmp_fd = open(bmp_path,O_RDWR);
	
	//读取14个字节的文件头信息
	read(bmp_fd,&fil,sizeof(fil));
	//读取40个字节的位图信息头信息
	read(bmp_fd,&inf,sizeof(inf));
	
	int wid = inf.biWidth; //bmp 宽
	int hig = inf.biHeight;//bmp 高
	int x_e = x_s + wid;//x坐标的结尾
	int y_e = y_s + hig;//y坐标的结尾
	
	char *bmp_buf = (char*)malloc(sizeof(char)*wid*hig*3);
	int  bmp_show[480*800] = {0};
	int  lcd_buf[480*800] = {0};
	
	printf("wid:%d hig:%d x_s:%d y_s:%d\n",wid,hig,x_s,y_s );
	//打开图片
	

	if(bmp_fd < 0)
	{
		printf("open bmp %s error!\n",bmp_path);
		return ;
	}
	
	//读取其余的像素数据
	read(bmp_fd,bmp_buf,wid*hig*3);
	
	
	//数据处理
	int i,j;
	for(i = 0,j = 0;i < wid*hig;i++,j+=3)
	{
		lcd_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j];
		//					  r			  g			          b
	
	}
	
	//显示位置
	int x,y;
	for(y = 0;y < hig;y++)
		for(x = 0;x < wid;x++)
		{
			//上下颠倒
			*(lcd+(y_e-y-1)*800+(x_s+x)) = lcd_buf[(y*wid)+x];
		}

	//write(lcd_fd,lcd_buf,sizeof(lcd_buf));
	
	
	//关闭图片
	close(bmp_fd);
}

void show_bmp_file(char *bmp_path)
{
	BITMAPFILEHEADER  fil;//14字节 文件头
	BITMAPINFOHEADER  inf;
	
	int bmp_fd = open(bmp_path,O_RDWR);
	
	//读取14个字节的文件头信息
	read(bmp_fd,&fil,sizeof(fil));
	//读取40个字节的位图信息头信息
	read(bmp_fd,&inf,sizeof(inf));
	
	int wid = inf.biWidth; //bmp 宽
	int hig = inf.biHeight;//bmp 高
	int x_s=(800-wid)/2;
	int y_s=(480-hig)/2;
	int x_e = x_s + wid;//x坐标的结尾
	int y_e = y_s + hig;//y坐标的结尾
	
	char *bmp_buf = (char*)malloc(sizeof(char)*wid*hig*3);
	int  bmp_show[480*800] = {0};
	int  lcd_buf[480*800] = {0};
	
	//打开图片
	

	if(bmp_fd < 0)
	{
		printf("open bmp %s error!\n",bmp_path);
	}
	
	//读取其余的像素数据
	read(bmp_fd,bmp_buf,wid*hig*3);
	
	
	//数据处理
	int i,j;
	for(i = 0,j = 0;i < wid*hig;i++,j+=3)
	{
		lcd_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j];
		//					  r			  g			          b
	
	}
	
	//显示位置
	int x,y;
	for(y = 0;y < hig;y++)
		for(x = 0;x < wid;x++)
		{
			//上下颠倒
			*(lcd+(y_e-y-1)*800+(x_s+x)) = lcd_buf[(y*wid)+x];
		}
//	write(lcd_fd,lcd_buf,sizeof(lcd_buf));
	
	//关闭图片
	close(bmp_fd);
}

void clear_screen(){
	int x,y;
	for( y=0;y<HEIGHT;y++)
		for(x=0;x<WIDTH;x++){
			//printf("x:%d y:%d\n",x,y);
			*(lcd+y*800+x)=0;
		}
}	
GLOBAL(int)	show_JPEG_file (char * filename)
{

  struct jpeg_decompress_struct cinfo;

  struct my_error_mgr jerr;
  /* More stuff */
  FILE * infile;		/* source file */
  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */


  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return 0;
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  // /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp(jerr.setjmp_buffer)) {

    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }
  
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */
	
  (void) jpeg_read_header(&cinfo, TRUE);

  (void) jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;
  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	char r,g,b;
	int color;
  int height=cinfo.output_height;
  int width=cinfo.output_width;
	int x_s=(800-width)/2;
  int y_s=(480-height)/2;
  int x_e=x_s+width;
  int y_e=y_s+height;
  int x,y;

  while (cinfo.output_scanline < cinfo.output_height) 
  {

  	y = cinfo.output_scanline;
      (void) jpeg_read_scanlines(&cinfo, buffer, 1);
  	//buffer :一行的rgb数据
  	char *p = buffer[0];
  	for(x=0;x<cinfo.output_width;x++)
  	{

  		r = *p++;
  		g = *p++;
  		b = *p++;
  		//argb
  		color =  r <<16 | g << 8 | b;
	
  		*(lcd+(y_s+y-1)*800+(x_s+x)) = color;
  	}
   
  }

  /* Step 7: Finish decompression */

  (void) jpeg_finish_decompress(&cinfo);

  jpeg_destroy_decompress(&cinfo);

  fclose(infile);

  return 1;
}

void readPicList(char* dirPath){
	int i;
	int pic_index=0;
	DIR* dir=opendir(dirPath);
	struct dirent* list;

	while((list=readdir(dir))!=NULL)
	{
		if(list->d_type==4)
			continue;
		
		else if(is_File(list->d_name,".jpeg")){
			filePic[pic_index].file_type=1;
			strcpy(filePic[pic_index].path,list->d_name);
			printf("in readPicLiat: %s %d\n",filePic[pic_index].path,filePic[pic_index].file_type);
			pic_index++;
		}

		else if(is_File(list->d_name,".bmp")){
			filePic[pic_index].file_type=0;
			strcpy(filePic[pic_index].path,list->d_name);
			printf("in readPicLiat: %s %d\n",filePic[pic_index].path,filePic[pic_index].file_type);
			pic_index++;
		}
		
		
	}
	
	sum_pic=pic_index;
	pic_index=0;
	return ;
}


int is_File(char* s1,const char* s2)
{
	if(strstr(s1,s2)!=NULL)
		return 1;
	return 0;
}

METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}
