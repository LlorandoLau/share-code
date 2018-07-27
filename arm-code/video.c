#include "header.h"
char video[20][20];
char order[20];
int video_index=0;
int sum_video=0;
int fi;
void readVideoList(char*);
void showVideoComponent();
void nextVideo();
void lastVideo();
/*往管道文件中写命令，输出到mpalyer的从模式下，接收到命令后去运行*/
void send_cmd(char *cmd)
{
	write(fi,cmd,strlen(cmd));
}

void mplayer_init()
{
	//判断管道文件是否存在
	if(access("/tmp/fifo",F_OK))
	{
		//不存在则创建
		mkfifo("/tmp/fifo",0777);
	}
	//打开管道文件
	fi = open("/tmp/fifo",O_RDWR);
}

int main()
{
	int x,y;
	readVideoList("./video");
	int ts_fd = open("/dev/input/event0",O_RDWR);
	if(ts_fd<0){
		printf("Failed to open ts_fd\n");
		return;
	}
	lcd_fd=open("/dev/fb0",O_RDWR);
	if(lcd_fd<0)
	{
		printf("FAILED TO OPEN LCD_FD\n");
		return;
	}	
	lcd = mmap(NULL, 
				800*480*4, 
				PROT_READ|PROT_WRITE,
				MAP_SHARED,
				lcd_fd, 
				0);
	if(lcd==NULL){
		printf("Failed to mmap\n");
		return;
	}
	//showVideoComponent();
	mplayer_init();
	
	system("./mplayer -slave -quiet -input file=/tmp/fifo -geometry 0:0 -zoom -x 800 -y 480 Faded3.avi &");
	
	struct input_event buf;
	
	//打开触摸屏
	int fd = open("/dev/input/event0",O_RDWR);
	
	while(1)
	{
		//读取触摸屏的值
		read(fd,&buf,sizeof(buf));
		
		if(buf.type == EV_ABS && buf.code == ABS_X)
		{
			x = buf.value;
		}
		
		if(buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
		{
			int pos=videoZone(x,y);
			switch(pos){
				case 1:	send_cmd("volume 10");	break;
				case 2:	send_cmd("volume -10");	break;
				case 3:	send_cmd("mute 0");		break;
				case 4:	send_cmd("seek 10");	break;
				case 5: send_cmd("seek -10");	break;
				case 6:	nextVideo();	break;
				case 7:lastVideo();	break;
				case 0:return 0;
			}
		}
	}
	
	close(fd);
}

void lastVideo()
{
	if(video_index==0)
		return;
	strcpy(order,"loadfile ");
	strcat(order,video[video_index])	;
	send_cmd(order);
	video_index--;
}

void nextVideo()
{
	if(video_index==sum_video-1)
		return;
	strcpy(order,"loadfile ");
	strcat(order,video[video_index]);	
	send_cmd(order);
	video_index++;
}

void readVideoList(char* dirPath)
{
	int i;
	int pic_index=0;
	DIR* dir=opendir(dirPath);
	struct dirent* list;

	while((list=readdir(dir))!=NULL)
	{
		if(list->d_type==4)
			continue;
		
		else if(is_File(list->d_name,".avi")){
			strcpy(video[video_index], dirPath);
			strcat(video[video_index]," ");
			printf("%s\n", video[video_index]);
			strcat(video[video_index],list->d_name);
			printf("in readPicLiat: %s\n",video[video_index]);
			video_index++;
		}
		
	}
	
	sum_video=video_index;
	video_index=0;
	return ;
}

int videoZone(int x,int y)
{
	if(y>=300 && y<400)
	{
		if(x>=0 && x<120)
			return 1;
		if(x>=120 && x<250)
			return 2;
		if(x>=250 && x<360)
			return 3;
		if(x>=360 && x<480)
			return 4;
		if(x>=480 && x<580)
			return 5;
		if(x>=580 && x<670)
			return 6;
		if(x>=670 && x<800)
			return 7;

	}
	if(x>=700 && x<800 && y>=0 && y<100)
		return 0;
}

