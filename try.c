#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

int fi;

void send_cmd(char* cmd)
{
	write(fi,cmd,strlen(cmd));
}

void mplayer_init()
{
	if(access("/tmp/fifo",F_OK))
		mkfifo("/tmp/fifo",0777);
	fi=open("/tmp/fifo",O_RDWR);
}

int main(int argc, char const *argv[])
{
	mplayer_init();
	system("./mplayer -slave -quiet -input file=/tmp/fifo -geometry 0:0 -zoom -x 800 -y 480 Faded3.avi &");

	struct input_event buf;
	int x,y;

	int fd=open("/dev/input/event0",O_RDWR);

	while(1)
	{
		read(fd,&buf,sizeof(buf));

		if(buf.type==EV_ABS && buf.code==ABS_X)
			x=buf.value;
		if(buf.type==EV_KEY && buf.code== BTN_TOUCH && buf.value==0)
		{
			if(x<400)
				send_cmd("mute 0\n");
			if(x>400)
				send_cmd("mute 1\n");
			
		}
	}
	close(fd);
	return 0;
}