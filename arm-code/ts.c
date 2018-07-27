#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/input.h>
int main()
{
	struct input_event ts;

	//打开触摸屏
	int ts_fd = open("/dev/input/event0",O_RDWR);
	if(ts_fd == -1)
    {
        printf("open ts fail\n");
        return -1;
    }
	int x,y;
	
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
		
		printf("x = %d ,y = %d\n",x,y);
		
	}
	//关闭触摸屏
	close(ts_fd);
	return 0;
}