 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/mman.h>
 void drv(int *lcd,int x,int y,int s_buf[480*800])
 {
	lcd = lcd+x+y*800;
	int i,j,a,b;
	for(i=0;i<100;i++)
		for(j=0;j<60;j++)
		{
			*(lcd+i*800+j) = s_buf[j*100+i];
		}
 }
int main()
{
	char bmp_buf[800*480*3]= {0};
	// bmp_buf[0] = b
	// bmp_buf[1] = g
	// bmp_buf[2] = r
	// bmp_buf[3] = b
	//        [4] = g
	//		  [5] = r
	//		  ````
	int  lcd_buf[800*480] = {0};
	int  show_bmp[800*480] = {0};
	int  s_buf[800*480] = {0};
	//打开lcd
	int lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd == -1)
	{
		printf("open lcd fail\n");
		return -1;
	}
	
	//打开bmp
	int bmp_fd = open("1.bmp",O_RDWR);
	if(bmp_fd == -1)
	{
		printf("open bmp  fail\n");
		return -1;
	}	
	//跳过头信息 54个字节
	lseek(bmp_fd,54,SEEK_SET);
	
	//读取bmp数据 1152000个字节
	read(bmp_fd,bmp_buf,sizeof(bmp_buf));
	
	//对数据进行处理 把像素24bit转化为32bits
	int i,j;
	for(i=0,j=0;i < 480*800;i++,j+=3)
	{
		lcd_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j]; //0x 00ff00
	}//                r               g            b
	
	//上下翻转
	int x,y,a,b;
	for(y = 0; y < 480;y++)
		for(x = 0; x < 800;x++)
		{
			show_bmp[(479-y)*800+x] = lcd_buf[y*800+x]; 
		}

		for(x=0,a = 0; a < 480;x++,a+=8)
		for(y=0,b = 0; b < 800;y++,b+=8)
		{
			s_buf[y*100+x]=show_bmp[a*800+b] ;
		}
	//显示到lcd上
		int *lcd = mmap(NULL,
					800*480*4,
					PROT_READ|PROT_WRITE,
					MAP_SHARED,
					lcd_fd,
					0);
		drv(lcd,200,100,s_buf);
			munmap(lcd,800*480*4);
	
	//关闭bmp
	close(bmp_fd);	
	//关闭lcd
	close(lcd_fd);
	return 0;
}
