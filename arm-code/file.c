#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	//int buf[480*800] = {0};
	int buf[480][800] = {0};
	
	//打开文件
	int fd = open("/dev/fb0",O_RDWR); 
	//判断打开是否成功
	if(fd == -1)
	{
		printf("open file fail\n");
		return -1;
	}
	int x,y;
printf("123\n");
	
	
	//初始化数组
	for(y = 0;y < 480;y++)
		for(x = 0;x < 800;x++)
		{
			buf[y][x] = 0x00ff00;
						//r g b						
		}
	printf("123\n");
	
	//写文件
	write(fd,buf,sizeof(buf));
	
	//关闭文件
	close(fd);
	return 0;
}
