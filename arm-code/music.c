#include "header.h"
int main()
{
	int x,y;
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
//	show_MusicComponent();
	readMusicList("./music");
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
			int pos=musicPos(x,y);
			switch(pos)
			{
				case 0:	return 0;
				case 1:
					nextSong();
					break;
				case 2:
					LastSong();
					break;
				case 3:
					playMusic();
					break;
				case 4:
					stopMusic();
					break;
			}
		}
	}
}

void nextSong()
{
	if(music_index==sum_music-1)
		return;
	music_index++;
	playMusic();
}

void LastSong()
{
	if(music_index==0)
		return;
	music_index--;
	playMusic();
}

void stopMusic()
{
	system("killall -19 madplay &");
}

void playMusic()
{
	int status=system("killall -18 madplay &");
	if(status<=0)
	{
		char order[20];
		strcpy(order,"./madplay ");
		strcat(order,music[music_index]);
		strcat(order," &");
		system(order);
	}
}

int musicPos(int x,int y)
{
	if((x>=700 && x<800) && (y>=0 && y<100))
		return 0;
	if((x>=25 && x<75) && (y>=380 && y<530))
		return 1;
	if((x>=95 && x<135) && (y>=380 && y<530))
		return 2;
	if((x>=155 && x<205) && (y>=380 && y<530))
		return 3;
	if((x>=225 && x<275) && (y>=380 && y<530))
		return 4;
}
void readMusicList(char *dirPath)
{
	int i;
	int pic_index=0;
	DIR* dir=opendir(dirPath);
	struct dirent* list;

	while((list=readdir(dir))!=NULL)
	{
		if(list->d_type==4)
			continue;
		
		else if(is_File(list->d_name,".mp3")){
			strcpy(music[music_index],dirPath);
			strcat(music[music_index],"/");
			strcat(music[music_index],list->d_name);
			printf("in readPicLiat: %s\n",music[music_index]);
			music_index++;
		}
		
	}
	
	sum_music=music_index;
	music_index=0;
	return ;
}