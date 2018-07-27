#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>

static struct termios initial_settings,new_settings;
static int peek=-1;

void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

int main()
{
	int ch=0;

	init_keyboard();
	while(ch!='q')
	{
		printf("Looping\n");
		sleep(1);
		if(kbhit())
		{
			ch=readch();
			printf("you hit %c\n", ch);
		}
	}
	close_keyboard();
	exit(0);
}

void init_keyboard()
{
	/*获取标准输入当前的设置，并保存到initial_settings
	news_settings是副本，程序只对副本进行操作，
	方便结束的时候恢复
	*/
	tcgetattr(0,&initial_settings);
	new_settings=initial_settings;
	new_settings.c_lflag &=~ICANON;
	new_settings.c_lflag &=~ECHO;
	new_settings.c_lflag &=~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] =0;
	tcsetattr(0,TCSANOW,&new_settings);
}
void close_keyboard()
{
	tcsetattr(0,TCSANOW,&initial_settings);
}

int kbhit()
{
	char ch;
	int nread;

	if(peek != -1)
	{
		return 1;
	}
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0,TCSANOW,&new_settings);
	nread=read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0,TCSANOW,&new_settings);

	if(nread==1)
	{
		peek=ch;
		return 1;
	}
	return 0;
}
int readch()
{
	char ch;

	if(peek != -1)
	{
		ch=peek;
		peek=-1;
		return ch;
	}
	read(0,&ch,1);
	return ch;
}